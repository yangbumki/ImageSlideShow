//���� ���̺귯��
#include <iostream>
#include <string>
#include <vector>

//�ܺ� ���̺귯��
#include "opencv2/opencv.hpp"

//��ó�� ���þ�
#define DEBUGGING				1
#define RELEASE					0

#define INIT_WIDTH				1280
#define INIT_HEIGHT				720

#define TICK_TIME				1500

#define ESC						27
#define ENTER					13

//���̺귯�� ��ũ
//����� ���̺귯��
#if DEBUGGING
#pragma comment(lib, "opencv_world4100d.lib")
//������ ���̺귯��
#elif RELEASE
#pragma comment(lib, "opencv_world4100.lib")
#endif

//���� ����
const char* windowTitle = "image";

//���� �Լ�
//void ErrorMessage(const char* msg) {
//	std::cerr << "[ERROR] : " << msg << std::endl;
//	exit(-1);
//}

void ErrorMessage(const std::string msg) {
	std::cerr << "[ERROR] : " << msg << std::endl;
	exit(-1);
}

int main(void) {
	//Ž�� �� �̹��� ���� ���� ����
	std::string pattern = ".\\images\\*.jpg";
	//�̹��� ���� �̸� ���� ���� ����
	std::vector<std::string> img_files{};
	//�̹��� ������ ���� ���� ����
	std::vector<cv::Mat> imgDatas{};

	//�̹��� ���� Ž��
	cv::glob(pattern, img_files);

	//.jpg ������ ���� ���
	if (img_files.empty()) ErrorMessage("Failed to find JPG files");

	//�ε��� ��ȣ
	int idx = 0;
	//�̹��� ��ü ����
	int cnt = (int)img_files.size();
	//�̹��� ������ �ҷ�����
	for (idx = 0; idx < cnt; idx++) {
		//�̹��� �ҷ�����
		cv::Mat img = cv::imread(img_files[idx]);
		//�̹��� �ҷ����� �������� ���
		if (img.empty()) ErrorMessage("Failed to load JPG files");
		//�̹��� ������ �ֱ�
		imgDatas.push_back(img);
	}

	//�ʱ� ������ ������ ����
	cv::Size initSize(INIT_WIDTH, INIT_HEIGHT);
	//�ҷ��� ���� �̸��� ������ ����
	cv::namedWindow(windowTitle, cv::WINDOW_NORMAL);
	//������ ������ �ʱ� ������ ����
	cv::resizeWindow(windowTitle, initSize);

	//�����̵� ���� ����
	bool slideEnable = true;
	//������ â ���� ����
	bool wndfScreen = false;
	//idx �� �ʱ�ȭ
	idx = 0;

	while (slideEnable) {
		//������ �ҷ��� �̹��� �� ������ ����
		cv::imshow(windowTitle, imgDatas[idx]);

		switch (cv::waitKey(TICK_TIME)) {
		case ESC:
			//while �� ���� ��ȣ ����
			slideEnable = false;
			break;
		case ENTER: {
			//������ ���� �Ӽ� �� ��������
			//auto oriProperty = cv::getWindowProperty(windowTitle, cv::WND_PROP_FULLSCREEN);
			//�ش� ������ ���� �Ӽ��� WINDOW_NORMAL �̱⿡ ���� �� �����

			//������ ���� ����
			wndfScreen = !wndfScreen;

			//������ �Ӽ� ����
			if (wndfScreen) {
				//��üȭ��
				cv::setWindowProperty(windowTitle, cv::WND_PROP_FULLSCREEN, cv::WINDOW_FULLSCREEN);
				//��üȭ�� �ƴ� ���
			}
			else {
				cv::setWindowProperty(windowTitle, cv::WND_PROP_FULLSCREEN, cv::WINDOW_NORMAL);
			}
		}
		default:
			//idx ���� ��ü �̹��� ������ ������ �ʱ�ȭ
			if (++idx >= cnt) idx = 0;
		}
	}

	//������ ����
	cv::destroyAllWindows();

	return 0;
}