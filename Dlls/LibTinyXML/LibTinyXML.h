#pragma once

// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the VMXLIBXMLIO_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// LIBTINYXML_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef LIBTINYXML_EXPORTS
#define LIBTINYXML_API __declspec(dllexport)
#else
#define LIBTINYXML_API __declspec(dllimport)
#endif

#include <string>
//#include <Windows.h>
#include "tinyxml.h"
#include <map>
#include <vector>
#include <iostream>

#define XML_FILE "ikk_doc.xml"
#define NAME_LENGTH 256 // 名字类字符的分配长度
#define VALUE_LENGTH 128 // the value's length
#define SAFE_DELETE(x) {if(x) delete x; x=nullptr;} // 安全删除new分配出来的变量
#define SAFE_DELETE_ARRAY(x) {if(x) delete[] x; x=nullptr;} // 安全删除new分配
typedef unsigned int uint32;

namespace avs
{

	#ifndef ENUMXMLSETTINGTYPE
	#define ENUMXMLSETTINGTYPE
	enum LIBTINYXML_API EnumXMLSettingType
	{
		STXML_Controller,
		STXML_ControllerCreationParam,
		STXML_MainCamera,
		STXML_AFCamera,
		STXML_PrevCamera,
		STXML_ScanSetting,
		STXML_Calibration,
		STXML_Autofocus,
		STXML_ImgProc,
		STXML_TBDiagnosis,
		STXML_PreTBAreaThr,
		STXML_PrevImgFgExtrParam,
		STXML_Item,
		STXML_ImageDealLinkSet,
		STXML_SettingTypeMax
	};
	#endif	//#ifndef ENUMXMLSETTINGTYPE

	#ifndef PARAMATTRIBUTE
	#define PARAMATTRIBUTE
	struct LIBTINYXML_API ParamAttribute
	{
		char sName[ NAME_LENGTH ];		//attribute name
		char sValue[ VALUE_LENGTH ];	//attribute value
		char sParentName[ NAME_LENGTH ];
		bool bSupChild;

		ParamAttribute()
		{
			sName[0]	= 0;
			sValue[0]	= 0;
			strcpy_s(sParentName, "");
			bSupChild	= false;
		}
	};
	#endif	//#ifndef PARAMATTRIBUTE

	#ifndef PARAMINFO
	#define PARAMINFO
	struct LIBTINYXML_API ParamInfo
	{
		char sName[ NAME_LENGTH ];		//attribute name
		char sValue[ VALUE_LENGTH ];	//attribute value
		std::vector<std::string> vctParentName;
		bool bSupChild;

		ParamInfo()
		{
			sName[0]	= 0;
			sValue[0]	= 0;
			bSupChild	= false;
		}
	};
	#endif	//#ifndef PARAMINFO

	#ifndef ENUM_XML_NODE_TYPE
	#define ENUM_XML_NODE_TYPE
	enum LIBTINYXML_API EnumXmlNodeType
	{
		XMLNT_ADD,
		XMLNT_MODIFY,
	};
	#endif	//#ifndef ENUM_XML_NODE_TYPE

	LIBTINYXML_API std::string getXMLSettingTypeName(EnumXMLSettingType id);

	LIBTINYXML_API bool getNodePointerByName(TiXmlElement* pElement, const char *strNodeName, const char *strTpyeName, TiXmlElement* &Node);

	LIBTINYXML_API bool createXmlFile(const char* szConfigFile);

	/**
	* @brief read information to map from XML file 
	*
	* @param propertiesMap	[out] the first is property,the second is value
	* @param szConfigFile	[in] filename
	* @param enumST			[in] xml file need set type
	*
	* @note filename without the path.
	*
	* @return True if successful; False if failed.;
	*/
	LIBTINYXML_API bool readXmlFile(std::map<std::wstring, std::wstring> &propertiesMap, const char *szConfigFile, EnumXMLSettingType enumST);

	LIBTINYXML_API bool readXmlFile(std::map<std::wstring, std::wstring> &propertiesMap, const char *szConfigFile, const char* strTypeName = "item");

	/**
	* @brief write the properties information to xml file
	*
	* @param propertiesMap	[out] the first is property,the second is value
	* @param szConfigFile	[in] filename
	* @param enumST			[in] xml file need set type
	*
	* @note filename without the path.
	*
	* @see EnumXMLSettingType
	*
	* @return True if successful; False if failed.;
	*/
	LIBTINYXML_API bool writeXmlFile(std::map<std::wstring, std::wstring> &propertiesMap, const char* szConfigFile, EnumXMLSettingType enumST);

	LIBTINYXML_API bool writeXmlFile(std::map<std::wstring, std::wstring> &propertiesMap, const char* szConfigFile, const char* strTypeName = "item");

	LIBTINYXML_API bool writeXmlFileVector(std::vector<ParamInfo>& vecPAttri, const char* szConfigFile, const char *strTypeName);

	LIBTINYXML_API	bool writeXmlFileVector(std::vector<ParamAttribute>& vecPAttri, const char* szConfigFile, const char *strTypeName);

	LIBTINYXML_API	bool readXmlFileVector(std::vector<ParamAttribute>& vecPAttri, const char *szConfigFile, const char *strTypeName);

	LIBTINYXML_API bool readXmlFileVector(std::vector<ParamInfo>& vecPAttri, const char *szConfigFile, const char *strTypeName);

	/**
	* @brief find value of a property from propertiesMap
	*
	* @param propertiesMap	[in] the first is property,the second is value
	* @param strProp		[in] find value of the property
	*
	* @return value of the property.;
	*
	* @author 2016/5/31 zxm
	*/
	LIBTINYXML_API std::wstring getMapValue(std::map<std::wstring, std::wstring> propertiesMap, std::wstring strProp);
	LIBTINYXML_API std::string getMapValueString(std::map<std::wstring, std::wstring> propertiesMap, std::wstring strProp);

	/**
	* @brief get int of a property from propertiesMap
	*
	* @param propertiesMap	[in] the first is property,the second is value
	* @param strProp		[in] find value of the property
	*
	* @return int of the property.;
	*/
	LIBTINYXML_API int getMapValueInt(std::map<std::wstring, std::wstring> propertiesMap, std::wstring strProp);

	/**
	* @brief get double of a property from propertiesMap
	*
	* @param propertiesMap	[in] the first is property,the second is value
	* @param strProp		[in] find value of the property
	*
	* @return double of the property.;
	*/
	LIBTINYXML_API double getMapValueDouble(std::map<std::wstring, std::wstring> propertiesMap, std::wstring strProp);

	/**
	* @brief judge the property whether exist
	*
	* @param propertiesMap	[in] the first is property,the second is value
	* @param strProp		[in] find value of the property
	*
	* @return True if successful; False if failed.;
	*/
	LIBTINYXML_API bool isExistProp(std::map<std::wstring, std::wstring> propertiesMap, std::wstring strProp);

}