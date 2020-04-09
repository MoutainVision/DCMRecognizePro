// LibTinyXMLIO.cpp : Defines the exported functions for the DLL application.
//
#include "LibTinyXML.h"

#include<fstream>

//	#ifdef _DEBUG
//		#pragma comment(lib,"tinyxmld.lib")
//	#else
//		#pragma comment(lib,"tinyxml.lib")
//	#endif

using std::ifstream;

namespace avs
{

	std::string wcs2mbs_xml(const wchar_t *pwc)
	{
		int nSize = 100;

		if (pwc == nullptr)
			return "";

		int len = wcslen(pwc);
		char *pmb = (char *)malloc(nSize);
		memset(pmb, 0, nSize);

		size_t conCharsNum = 0;
		int i = wcstombs_s(&conCharsNum, pmb, nSize, pwc, nSize);

		std::string buf = pmb;

		free(pmb);

		return buf;
	}

	std::wstring mbs2wcs_xml(const char *pmb)
	{
		int nSize = 100;

		int len = strlen(pmb);
		wchar_t *pwc = (wchar_t *)malloc(nSize);
		memset(pwc, 0, nSize);

		size_t conWcharsNum = 0;
		int i = mbstowcs_s(&conWcharsNum, pwc, nSize, pmb, nSize);

		std::wstring buf = pwc;

		free(pwc);

		return buf;
	}

	#ifndef AVS_TAGITEM
	#define AVS_TAGITEM
	struct tagItem
	{
		std::string strName;
		EnumXMLSettingType id;
	};
	#endif	//#ifndef AVS_TAGITEM

	tagItem itemXMLSettingType[] = 
	{
		{ "Controller", STXML_Controller },
		{ "ControllerCreationParam", STXML_ControllerCreationParam },
		{ "MainCamera", STXML_MainCamera },
		{ "AFCamera", STXML_AFCamera },
		{ "PrevCamera", STXML_PrevCamera },
		{ "ScanSetting", STXML_ScanSetting },
		{ "Calibration", STXML_Calibration },
		{ "Autofocus", STXML_Autofocus },
		{ "ImgProc", STXML_ImgProc },
		{ "TBDiagnosis", STXML_TBDiagnosis },
		{ "PreTBAreaThr", STXML_PreTBAreaThr },
		{ "PrevImgFgExtrParam", STXML_PrevImgFgExtrParam },
		{ "item", STXML_Item },
		{ "CvmxImageDealLinkingSet",STXML_ImageDealLinkSet},
	};

	bool fileExist(const char* lpFileName) 
	{
		ifstream f(lpFileName);
		return f.good();
	}

	std::string getXMLSettingTypeName(EnumXMLSettingType id)
	{
		return itemXMLSettingType[id].strName;
	}

	void mapToVector(std::map<std::wstring, std::wstring> propertiesMap, std::vector<ParamAttribute>& vecPAttri)
	{
		ParamAttribute pa;

		std::map<std::wstring,std::wstring>::const_iterator iter;
		for (iter=propertiesMap.begin();iter!=propertiesMap.end();iter++)
		{
			strcpy_s(pa.sName, wcs2mbs_xml(iter->first.c_str()).c_str());
			strcpy_s(pa.sValue, wcs2mbs_xml(iter->second.c_str()).c_str());
			vecPAttri.push_back(pa);
		}
	}

	void vectorToMat(std::map<std::wstring, std::wstring>& propertiesMap, std::vector<ParamAttribute> vecPAttri)
	{
		wchar_t szFirst[NAME_LENGTH];
		wchar_t szSecond[NAME_LENGTH];

		for (int i=0; i<(int)vecPAttri.size(); i++)
		{
			wcscpy_s(szFirst, mbs2wcs_xml(vecPAttri[i].sName).c_str());
			wcscpy_s(szSecond, mbs2wcs_xml(vecPAttri[i].sValue).c_str());
			propertiesMap.insert(std::make_pair(szFirst, szSecond));;
		}
	}

	bool getNodePointerByName(TiXmlElement* pElement, const char *strNodeName, const char *strTpyeName, TiXmlElement* &Node)
	{
		//TiXmlElement *pElement = myDocument->RootElement();
		if (nullptr == pElement)
			return false;

		TiXmlElement *temproot = pElement;
		//pRootEle = pRootEle->FirstChild("libs")->ToElement();
		for (temproot = pElement->FirstChildElement();temproot;temproot = temproot->NextSiblingElement())
			if (0 == strcmp(strNodeName,temproot->Value()))
			{
				Node = temproot;
				return true;
			}

		return false;
	}

	bool delNode(const char *xmlpath, char *strNodeName, char *strTpyeName)
	{
		bool flags = false;

		TiXmlDocument *pDoc = new TiXmlDocument();

		if (nullptr==pDoc)
		{
			goto END;
		}

		pDoc->LoadFile(xmlpath);
		TiXmlElement *pRootEle = pDoc->RootElement();

		if (nullptr==pRootEle)
		{
			goto END;
		}

		TiXmlElement *pNode = nullptr;
		getNodePointerByName(pRootEle, strNodeName,strTpyeName, pNode);//获取节点的位置。

		// 假如是根节点
		if (pRootEle==pNode)
		{
			if(pDoc->RemoveChild(pRootEle))
			{
				pDoc->SaveFile(xmlpath);
				goto END;
			}
			else
				goto END;
		}
		// 假如是其它节点
		if (nullptr!=pNode)
		{
			TiXmlNode *pParNode = pNode->Parent();
			if (nullptr==pParNode)
			{
				goto END;
			}

			TiXmlElement* pParentEle = pParNode->ToElement();
			if (nullptr!=pParentEle)
			{
				if(pParentEle->RemoveChild(pNode))//删除节点
					pDoc->SaveFile(xmlpath);//保存
				else
					goto END;
			}
		}
		else
		{
			goto END;
		}

		flags = true;

		END:
		if (pDoc != nullptr)
		{
			delete pDoc;
		}

		return flags;
	}

	bool modifyNode(TiXmlElement *pElement, const char *strNodeName, const char *strTypeName, const char *strText)
	{
		if (nullptr==pElement)
		{
			return false;
		}

		TiXmlElement *pNode = nullptr;
		getNodePointerByName(pElement,strNodeName,strTypeName,pNode);
		if (nullptr!=pNode)
		{
			pNode->FirstChild()->SetValue(strText);
			return true;
		}
		else
		{
			return false;
		}
	}

	bool addNode(TiXmlElement *pElement,char *strNodeName, char *strText)
	{
		if (nullptr == pElement)
		{
			return false;
		}

		//pElement = pElement->FirstChild("libs")->ToElement();//找到父节点libs位置
		if (nullptr!=pElement)
		{
			// 创建添加的子节点：pNewNode
			TiXmlElement *pNewNode = new TiXmlElement(strNodeName);
			if (nullptr==pNewNode)
			{
				return false;
			}

			TiXmlText *pVal = new TiXmlText(strText);
			pNewNode->InsertEndChild(*pVal);
			pElement->InsertEndChild(*pNewNode);//插入新子节点

			SAFE_DELETE(pNewNode);
			SAFE_DELETE(pVal);
			return true;
		}
		else
		{
			return false;
		}
	}

	bool createXmlFile(const char* szConfigFile)
	{
		if( !szConfigFile)
			return false;

		char sBuf[NAME_LENGTH]; // 一个临时存放的字符串
		char sFilePath[NAME_LENGTH]; //全路径文件名

		strcpy_s(sFilePath, szConfigFile);			

		TiXmlElement* pElm = nullptr; // 一个指向Element的指针
		TiXmlDeclaration Declaration( "1.0","gb2312", "yes" ); // 建立XML头结构
		TiXmlDocument xmlDoc( sFilePath ); // 用存档的文件名字来建立一个XML文件

		xmlDoc.InsertEndChild( Declaration ); // 把XML头结构插入当前文档

		// 插入根节点“ROOT”
		pElm = new TiXmlElement( "ROOT" ); // 建立根节点“ROOT”
		sprintf_s( sBuf, "%d", 0 );
		pElm->SetAttribute( "num", sBuf ); // 建立一个ROOT的子Element

		xmlDoc.InsertEndChild( *pElm );
		xmlDoc.SaveFile();
		SAFE_DELETE( pElm ); // 删除Element
		xmlDoc.Clear();

		return true;
	}

	void importData( TiXmlElement* pElm, std::vector<ParamAttribute>& vecPAttri, const char *strTypeName )
	{
		int i;
		//char sBuf[NAME_LENGTH]; // 一个临时存放的字符串
		TiXmlElement* pElmChild = nullptr; // 一个指向Element的指针
		TiXmlElement* pElmGrandChild = nullptr; // 一个指向Element的指针
		TiXmlText* pText = nullptr; // 一个指向Text的指针

		ParamAttribute pa;

		int nNum = atoi( pElm->Attribute( "num" ) );
		pElmChild = pElm->FirstChildElement();
		if(pElmChild)
			for( i=0; i<nNum; i++ )
			{
				if(pElmChild)
				{
					strcpy_s(pa.sName, pElmChild->Value());
					if(!pElmChild->NoChildren())
						strcpy_s(pa.sValue, pElmChild->FirstChild()->Value());
					else
						strcpy_s(pa.sValue, "");
					strcpy_s(pa.sParentName, strTypeName);
					pa.bSupChild = false;
					vecPAttri.push_back(pa);

					TiXmlElement *pNode = pElmChild;
					for (pNode = pElmChild->FirstChildElement();pNode;pNode = pNode->NextSiblingElement())
					{
						strcpy_s(pa.sName, pNode->Value());
						strcpy_s(pa.sValue, pNode->FirstChild()->Value());
						strcpy_s(pa.sParentName, pElmChild->Value());
						pa.bSupChild = true;
						vecPAttri.push_back(pa);
					}

					pElmChild = pElmChild->NextSiblingElement();
				}
			}
	}

	void importData(TiXmlElement* pElm, std::vector<ParamInfo>& vecPAttri, std::vector<std::string>& vctParentName)
	{
		TiXmlElement *pNode2 = pElm;
		std::vector<std::string> vctParentName2;
		for (pNode2 = pElm->FirstChildElement(); pNode2; pNode2 = pNode2->NextSiblingElement())
		{
			vctParentName2.clear();
			vctParentName2.assign(vctParentName.begin(), vctParentName.end());
			vctParentName2.push_back(pNode2->Parent()->Value());
			importData(pNode2, vecPAttri, vctParentName2);
		}

		ParamInfo pa;
		strcpy_s(pa.sName, pElm->Value());
		pa.vctParentName.assign(vctParentName.begin(), vctParentName.end());
		if (pElm->FirstChildElement())
		{
			strcpy_s(pa.sValue, "");
			pa.bSupChild = false;
		}
		else
		{
			if (pElm->FirstChild())
			{
				strcpy_s(pa.sValue, pElm->FirstChild()->Value());
				pa.bSupChild = true;
			}
		}
		vecPAttri.push_back(pa);
	}

	bool readXmlFileVector(std::vector<ParamInfo>& vecPAttri, const char *szConfigFile, const char *strTypeName)
	{
		if (!szConfigFile)
			return false; // 确定指针存在

		char sFilePath[NAME_LENGTH]; //全路径文件名

		char szError[NAME_LENGTH];
		memset(szError, 0x00, NAME_LENGTH);

		strcpy_s(sFilePath, szConfigFile);
		if (!fileExist(sFilePath))
		{
			strcat_s(szError, sFilePath);
			strcat_s(szError, " is not exist!!\n");
			printf("%s", szError);

			return false;
		}

		TiXmlElement* pElmChild = nullptr; // 一个指向Element的指针
		TiXmlDocument xmlDoc(sFilePath); // 输入XML路径

		if (!xmlDoc.LoadFile()) // 读取XML并检查是否读入正确
			return false;
		TiXmlElement* pElmRoot = nullptr; // 根节点
		pElmRoot = xmlDoc.FirstChildElement("ROOT"); // 得到根节点
		if (!pElmRoot)
		{
			return false;
		}

		//int i;
		int nNumRoot = atoi(pElmRoot->Attribute("num"));
		pElmChild = pElmRoot->FirstChildElement(strTypeName);
		if (pElmChild)
		{
			TiXmlElement *pNode1 = pElmChild;
			for (pNode1 = pElmChild->FirstChildElement(); pNode1; pNode1 = pNode1->NextSiblingElement())
			{
				std::vector<std::string> vctParentName;
				importData(pNode1, vecPAttri, vctParentName);
			}
		}

		return true;
	}

	bool readXmlFileVector(std::vector<ParamAttribute>& vecPAttri, const char *szConfigFile, const char *strTypeName)
	{
		if( !szConfigFile )
			return false; // 确定指针存在

		char sFilePath[NAME_LENGTH]; //全路径文件名

		char szError[NAME_LENGTH];
		memset(szError, 0x00, NAME_LENGTH);

		strcpy_s(sFilePath, szConfigFile);			
		if(!fileExist(sFilePath))
		{
			strcat_s(szError, sFilePath); 
			strcat_s(szError, " is not exist!!\n");
			printf("%s", szError);

			return false;
		}

		TiXmlElement* pElmChild = nullptr; // 一个指向Element的指针
		TiXmlDocument xmlDoc( sFilePath ); // 输入XML路径

		if( !xmlDoc.LoadFile() ) // 读取XML并检查是否读入正确
			return false;
		TiXmlElement* pElmRoot = nullptr; // 根节点
		pElmRoot = xmlDoc.FirstChildElement( "ROOT" ); // 得到根节点
		if( !pElmRoot )
		{
			return false;
		}

		//int i;
		int nNumRoot = atoi( pElmRoot->Attribute( "num" ) );
		pElmChild = pElmRoot->FirstChildElement( strTypeName );
		if(pElmChild)
			//for( i=0; i<nNumRoot; i++ )
			//{
			//	if(pElmChild)
			//	{
					importData( pElmChild, vecPAttri, strTypeName );
			//		pElmChild = pElmChild->NextSiblingElement(); // find next data
			//	}
			//}
		return true;
	}

	bool readXmlFile(std::map<std::wstring, std::wstring> &propertiesMap, const char *szConfigFile, EnumXMLSettingType enumST)
	{
		std::vector<ParamAttribute> vecPAttri;
		vecPAttri.clear();

		if(!readXmlFileVector(vecPAttri, szConfigFile, getXMLSettingTypeName(enumST).c_str()))
			return false;

		vectorToMat(propertiesMap, vecPAttri);

		return true;
	}

	bool readXmlFile(std::map<std::wstring, std::wstring> &propertiesMap, const char *szConfigFile, const char* strTypeName)
	{
		std::vector<ParamAttribute> vecPAttri;
		vecPAttri.clear();

		if(!readXmlFileVector(vecPAttri, szConfigFile, strTypeName))
			return false;

		vectorToMat(propertiesMap, vecPAttri);

		return true;
	}

	bool getRootNumAndNodetype(int &nNumRoot, EnumXmlNodeType &enumNodeType, char* sFilePath, const char *strNodeName)
	{
		TiXmlElement* pElmChild = nullptr; // 一个指向Element的指针
		TiXmlDocument xmlDoc( sFilePath ); // 用存档的文件名字来建立一个XML文件
		if(fileExist(sFilePath))
		{
			if( !xmlDoc.LoadFile() ) // 读取XML并检查是否读入正确
				return false;

			TiXmlElement* pElmRoot = nullptr; // 根节点
			pElmRoot = xmlDoc.FirstChildElement( "ROOT" ); // 得到根节点
			if(pElmRoot)
			{
				nNumRoot = atoi( pElmRoot->Attribute("num") );
				pElmChild = pElmRoot->FirstChildElement( strNodeName );
				if(pElmChild)
				{
					enumNodeType = XMLNT_MODIFY;
				}
				else
				{
					enumNodeType = XMLNT_ADD;
					nNumRoot++;
				}
			}
		}
		else
		{
			enumNodeType = XMLNT_ADD;
			nNumRoot = 1;
		}
		xmlDoc.Clear();

		return true;
	}

	bool writeXmlFileVector(std::vector<ParamInfo>& vecPAttri, const char* szConfigFile, const char *strTypeName)
	{
		if( !szConfigFile || vecPAttri.size() <= 0)
			return false;

		char sBuf[NAME_LENGTH]; // 一个临时存放的字符串
		char sFilePath[NAME_LENGTH]; //全路径文件名

		strcpy_s(sFilePath, szConfigFile);			

		if(!fileExist(sFilePath))
		{
			if(!createXmlFile(szConfigFile))
				return false;
		}

		for (int i = 0; i < vecPAttri.size(); i++)
		{
			TiXmlDocument xmlDoc( sFilePath ); // 输入XML路径

			if( !xmlDoc.LoadFile() ) // 读取XML并检查是否读入正确
				return false;
			TiXmlElement* pRoot = nullptr; // 根节点
			pRoot = xmlDoc.FirstChildElement( "ROOT" ); // 得到根节点

			int nCountRoot = 0;
			if (pRoot)
			{
				nCountRoot = atoi(pRoot->Attribute("num"));
				bool bNewType = false;	//是否是新的typename;
				TiXmlElement* pType = nullptr;
				pType = (TiXmlElement*)pRoot->LastChild(strTypeName);
				
				if (pType)
				{
					bNewType = false;
				}
				else
				{
					pType = new TiXmlElement(strTypeName);
					bNewType = true;
					nCountRoot++;
					sprintf_s(sBuf, "%d", nCountRoot);
					pRoot->SetAttribute("num", sBuf);
				}

				if (vecPAttri[i].vctParentName.size() <= 0)
				{
					TiXmlElement* pElemChild = (TiXmlElement*)pType->LastChild(vecPAttri[i].sName);
					if(!pElemChild)
					{
						{
							// 创建添加的子节点：pNewNode
							TiXmlElement newNode(vecPAttri[i].sName);

							TiXmlText *pVal = nullptr;
							if (vecPAttri[i].bSupChild)
							{
								pVal = new TiXmlText(vecPAttri[i].sValue);
								newNode.InsertEndChild(*pVal);
							}
							pType->InsertEndChild(newNode);//插入新子节点

							if (vecPAttri[i].bSupChild)
							{
								SAFE_DELETE(pVal);
							}
						}
					}
					else
					{
						if (vecPAttri[i].bSupChild)
						{
							if (pElemChild->FirstChild())
							{
								pElemChild->FirstChild()->SetValue(vecPAttri[i].sValue);
							}
							else
							{
								TiXmlText *pVal = nullptr;
								pVal = new TiXmlText(vecPAttri[i].sValue);
								pElemChild->InsertEndChild(*pVal);
								SAFE_DELETE(pVal);
							}
						}
					}
				}

				TiXmlElement* pParent = pType;
				for (int j = 0; j < vecPAttri[i].vctParentName.size(); j++)
				{
					TiXmlElement* pElemChild1 = (TiXmlElement*)pParent->LastChild(vecPAttri[i].vctParentName[j].c_str());
					if (pElemChild1)
					{
						TiXmlElement* pElemChild2 = (TiXmlElement*)pElemChild1->LastChild(vecPAttri[i].sName);
						if (pElemChild2)
						{
							if (vecPAttri[i].bSupChild && j == (vecPAttri[i].vctParentName.size() - 1))
							{
								if (pElemChild2->FirstChild())
								{
									pElemChild2->FirstChild()->SetValue(vecPAttri[i].sValue);
								}
								else
								{
									TiXmlText *pVal = nullptr;
									pVal = new TiXmlText(vecPAttri[i].sValue);
									pElemChild2->InsertEndChild(*pVal);
									SAFE_DELETE(pVal);
								}
							}
						}
						else
						{
							if (j == (vecPAttri[i].vctParentName.size() - 1))
							{
								// 创建添加的子节点：pNewNode
								TiXmlElement newNode(vecPAttri[i].sName);

								TiXmlText *pVal = nullptr;
								if (vecPAttri[i].bSupChild)
								{
									pVal = new TiXmlText(vecPAttri[i].sValue);
									newNode.InsertEndChild(*pVal);
								}
								pElemChild1->InsertEndChild(newNode);//插入新子节点

								if (vecPAttri[i].bSupChild)
								{
									SAFE_DELETE(pVal);
								}
							}
						}
						pParent = pElemChild1;
					}
				}

				if (bNewType)
				{
					pRoot->InsertEndChild(*pType);

					SAFE_DELETE(pType);
				}
			}

			xmlDoc.SaveFile();
			xmlDoc.Clear();
		}

		return true;
	}

	bool writeXmlFileVector(std::vector<ParamAttribute>& vecPAttri, const char* szConfigFile, const char *strTypeName)
	{
		if( !szConfigFile || vecPAttri.size() <= 0)
			return false;

		char sBuf[NAME_LENGTH]; // 一个临时存放的字符串
		char sFilePath[NAME_LENGTH]; //全路径文件名

		strcpy_s(sFilePath, szConfigFile);			

		if(!fileExist(sFilePath))
		{
			if(!createXmlFile(szConfigFile))
				return false;
		}

		int nNumRoot = 0;
		EnumXmlNodeType enumNodeType = XMLNT_ADD;

		getRootNumAndNodetype(nNumRoot, enumNodeType, sFilePath, strTypeName);

		TiXmlElement* pElmChild = nullptr; // 一个指向Element的指针
		TiXmlDocument xmlDoc( sFilePath ); // 输入XML路径

		if( !xmlDoc.LoadFile() ) // 读取XML并检查是否读入正确
			return false;
		TiXmlElement* pElm = nullptr; // 根节点
		pElm = xmlDoc.FirstChildElement( "ROOT" ); // 得到根节点

		sprintf_s( sBuf, "%d", nNumRoot );
		pElm->SetAttribute( "num", sBuf ); // 建立一个ROOT的子Element

		TiXmlElement* pNode = nullptr;

		int nCount = 0;
		if( pElm )
		{
			switch(enumNodeType)
			{
			case XMLNT_ADD:
				pNode = new TiXmlElement( strTypeName );
				nCount = 0;
				for(int i=0; i<(int)vecPAttri.size(); i++)
				{
					char strNodeName[ NAME_LENGTH ];
					TiXmlElement *pAdd = pNode;

					if( vecPAttri[i].bSupChild )
					{
						//if (strcmp(vecPAttri[i].sParentName, "") == 0)
						//{
							pAdd = (TiXmlElement *)pNode->LastChild( strNodeName );
						//}
						//else
						//{
						//	pAdd = (TiXmlElement *)pNode->LastChild( vecPAttri[i].sParentName );
						//}
					}
					else
					{
						pAdd = pNode;
						strcpy_s( strNodeName, vecPAttri[i].sName );
						nCount++;
					}

					if (strcmp(vecPAttri[i].sValue, "NaN") != 0)
					{
						if (!addNode(pAdd, vecPAttri[i].sName, vecPAttri[i].sValue))
							return false;
					}
					else
					{
						if (!addNode(pAdd, vecPAttri[i].sName, ""))
							return false;
					}
				}
				sprintf_s( sBuf, "%d", nCount );
				pNode->SetAttribute( "num", sBuf );
				pElm->InsertEndChild( *pNode );
				break;
			case XMLNT_MODIFY:
				pNode = pElm->FirstChildElement( strTypeName );
				nCount = atoi( pNode->Attribute("num") );
				for(int i=0; i<(int)vecPAttri.size(); i++)
				{
					TiXmlElement *pModi = pNode;
					char szName[ NAME_LENGTH ];
					char strNodeName[ NAME_LENGTH ];
					if( vecPAttri[i].bSupChild )
					{
						pModi = (TiXmlElement *)pNode->LastChild( strNodeName );
						strcpy_s( szName, pModi->Value() );
					}
					else
					{
						pModi = pNode;
						strcpy_s( szName, strTypeName );
						strcpy_s( strNodeName, vecPAttri[i].sName );
					}

					if (strcmp(vecPAttri[i].sValue, "NaN") != 0)
					{
						if(!modifyNode(pModi, vecPAttri[i].sName, szName, vecPAttri[i].sValue))
						{
							if(!addNode(pModi, vecPAttri[i].sName, vecPAttri[i].sValue))
								return false;
							else
								if( !vecPAttri[i].bSupChild )
								{
									nCount++;
								}
						}
					}
				}
				sprintf_s( sBuf, "%d", nCount );
				pNode->SetAttribute( "num", sBuf );
				break;
			}

		}
		xmlDoc.SaveFile();
		if(XMLNT_ADD == enumNodeType)
			SAFE_DELETE( pNode ); // 删除Element
		xmlDoc.Clear();

		return true;
	}

	bool writeXmlFile(std::map<std::wstring, std::wstring> &propertiesMap, const char* szConfigFile, EnumXMLSettingType enumST)
	{
		if( propertiesMap.size() <= 0)
			return false;

		std::vector<ParamAttribute> vecPAttri;
		vecPAttri.clear();
		mapToVector(propertiesMap, vecPAttri);

		return writeXmlFileVector(vecPAttri, szConfigFile, getXMLSettingTypeName(enumST).c_str());
	}

	bool writeXmlFile(std::map<std::wstring, std::wstring> &propertiesMap, const char* szConfigFile, const char* strTypeName)
	{
		if( propertiesMap.size() <= 0)
			return false;

		std::vector<ParamAttribute> vecPAttri;
		vecPAttri.clear();
		mapToVector(propertiesMap, vecPAttri);

		return writeXmlFileVector(vecPAttri, szConfigFile, strTypeName);
	}

	std::wstring getMapValue(std::map<std::wstring, std::wstring> propertiesMap, std::wstring strProp)
	{
		std::wstring wsBuf = L"";
		auto fnd = propertiesMap.find(strProp);
		if (propertiesMap.end() != fnd)
		{
			wsBuf = fnd->second;
		}

		return wsBuf;
	}

	std::string getMapValueString(std::map<std::wstring, std::wstring> propertiesMap, std::wstring strProp)
	{
		char cValue[100];
		wchar_t strValue[100];
		std::wstring wsValue = L"";
		wsValue = getMapValue(propertiesMap, strProp);
		wcscpy_s(strValue, wsValue.c_str());

		//strcpy_s(cValue, wcharToChar(strValue));
		sprintf_s(cValue, "%s", wcs2mbs_xml(strValue).c_str());
		int nLen = wcslen(strValue);
		cValue[nLen] = '\0';

		std::string str(cValue);

		return str;
	}

	int getMapValueInt(std::map<std::wstring, std::wstring> propertiesMap, std::wstring strProp)
	{
		wchar_t strValue[100];
		std::wstring wsValue = L"";
		int nValue = 0;

		wsValue = getMapValue(propertiesMap, strProp);
		wcscpy_s(strValue, wsValue.c_str());
		nValue = _wtoi(strValue);

		return nValue;
	}

	double getMapValueDouble(std::map<std::wstring, std::wstring> propertiesMap, std::wstring strProp)
	{
		wchar_t strValue[100];
		std::wstring wsValue = L"";
		double fValue = 0;

		wsValue = getMapValue(propertiesMap, strProp);
		wcscpy_s(strValue, wsValue.c_str());
		fValue = _wtof(strValue);

		return fValue;
	}

	bool isExistProp(std::map<std::wstring, std::wstring> propertiesMap, std::wstring strProp)
	{
		std::wstring wsBuf = L"";
		auto fnd = propertiesMap.find(strProp);
		if (propertiesMap.end() != fnd)
		{
			return true;
		}

		return false;
	}

}