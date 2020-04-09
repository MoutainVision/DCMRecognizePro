#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//   avs::xImage img;
//   img.load("F://1_3.JPG");
//   img.save("F://1_test.jpg");


    DcmFileFormat fileformat;

////   OFCondition oc = fileformat.loadFile("G:\\DCM\\ACC-AL6-1 90kv.DCM");

////   OFCondition oc = fileformat.loadFile("G:\\DCM\\CR\\演示文件2.DCM");

    OFCondition oc = fileformat.loadFile("G:\\DCM\\CR\\CR15-020-T10厚-450焦距6分50秒.DCM");
//    OFCondition oc = fileformat.loadFile("G:\\DCM\\CR\\ACC-AL6-1 90kv.DCM");

//    OFCondition oc = fileformat.loadFile("G:\\DCM\\CR\\演示文件2.DCM");






   if(oc.good()){

       OFString patientName;

      if(fileformat.getDataset()->findAndGetOFString(DCM_PatientName, patientName).good())

      {

      std::cout<<"Patient Name:"<<patientName<<std::endl;

      }

      DcmDataset *dataset = fileformat.getDataset();	//得到Dicom的数据集，所有的数据都存储在数据集当中
          E_TransferSyntax xfer = dataset->getOriginalXfer();	//得到传输语法

          OFString patientname;
          dataset->findAndGetOFString(DCM_PatientName, patientname);	//获取病人姓名     //dataset->findAndGetOFString/->findAndGetUint16
          std::cout << "patientName :" << patientname << std::endl;

          unsigned short bit_count(0);
          dataset->findAndGetUint16(DCM_BitsStored, bit_count);	//获取像素的位数 bit
          std::cout << "bit_count :" << bit_count << std::endl;

          OFString isRGB;
          dataset->findAndGetOFString(DCM_PhotometricInterpretation, isRGB);//DCM图片的图像模式
          std::cout << "isrgb :" << isRGB << std::endl;

          unsigned short img_bits(0);
          dataset->findAndGetUint16(DCM_SamplesPerPixel, img_bits);	//单个像素占用多少byte
          std::cout << "img_bits :" << img_bits << std::endl;
          //DicomImage* img_xfer = new DicomImage(xfer, 0, 0, 1);		//由传输语法得到图像的帧

          unsigned short m_width;		//获取图像的窗宽高
          unsigned short m_height;
          dataset->findAndGetUint16(DCM_Rows, m_height);
          dataset->findAndGetUint16(DCM_Columns, m_width);
          std::cout << "width :" << m_width << std::endl;
          std::cout << "height " << m_height << std::endl;

              unsigned short center, width;  //获取源图像中的窗位和窗宽
          dataset->findAndGetUint16(DCM_WindowCenter, center);
          dataset->findAndGetUint16(DCM_WindowWidth, width);

              DcmElement* element = NULL;    //读取dcm中的像素值
          OFCondition result = dataset->findAndGetElement(DCM_PixelData, element);
          if (result.bad() || element == NULL)
          {
              std::cout << "findAndGetElement result  bad. " << std::endl;
          }

          std::cout << element->getLength() << std::endl;


          Uint16* pixData16;
          result = element->getUint16Array(pixData16);
          if (result.bad())
          {
              std::cout << "getUint16Array result  bad. " << std::endl;
          }

//          for (int i = 0; i < 2000*2048; i++)
//                 *(pixData16 + i) *= 20; // 灰度拉伸


//         QImage img((const unsigned char *)(pixData16), 2000, 2048, 2000*3, QImage::Format_RGB32);


//         if (img.save("./test.jpg"))
//         {
//             std::cout << "save  bad. " << std::endl;
//         }


          //   avs::xImage img;
          //   img.load("F://1_3.JPG");
          //   img.save("F://1_test.jpg");

        avs::xImage *img = new avs::xImage();
//        img->create(m_width, m_height, bit_count, avs::XIMAGE_FORMAT_JPG);

        img->create(m_width, m_height, true, avs::PIXEL_FORMAT_MONO8);

        qDebug() << "11" << img->getImageSize();

        img->copyData((const unsigned char *)(pixData16), img->getImageSize());

        qDebug() << "22";

        img->save("./1_test1.jpg");




//          QImage img((const unsigned char *)(pixData16), m_width, m_height, m_width, QImage::Format_Grayscale8);


//          if (img.save("./test3.jpg"))
//          {
//              std::cout << "save  bad. " << std::endl;
//          }

   }
}

MainWindow::~MainWindow()
{
    delete ui;
}
