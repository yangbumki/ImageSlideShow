//내부 라이브러리
#include <iostream>
#include <string>
#include <vector>

//외부 라이브러리
#include "opencv2/opencv.hpp"

//전처리 지시어
#define DEBUGGING				1
#define RELEASE					0

#define INIT_WIDTH				1280
#define INIT_HEIGHT				720

#define TICK_TIME				1500

#define ESC						27
#define ENTER					13

//라이브러리 링크
//디버깅 라이브러리
#if DEBUGGING
#pragma comment(lib, "opencv_world4100d.lib")
//릴리즈 라이브러리
#elif RELEASE
#pragma comment(lib, "opencv_world4100.lib")
#endif

//전역 변수
const char* windowTitle = "image";

//공통 함수
//void ErrorMessage(const char* msg) {
//	std::cerr << "[ERROR] : " << msg << std::endl;
//	exit(-1);
//}

void ErrorMessage(const std::string msg) {
	std::cerr << "[ERROR] : " << msg << std::endl;
	exit(-1);
}

int main(void) {
	//탐색 할 이미지 파일 패턴 정의
	std::string pattern = ".\\images\\*.jpg";
	//이미지 파일 이름 저장 벡터 정의
	std::vector<std::string> img_files{};
	//이미지 데이터 저장 벡터 정의
	std::vector<cv::Mat> imgDatas{};

	//이미지 파일 탐색
	cv::glob(pattern, img_files);

	//.jpg 파일이 없을 경우
	if (img_files.empty()) ErrorMessage("Failed to find JPG files");

	//인덱스 번호
	int idx = 0;
	//이미지 전체 개수
	int cnt = (int)img_files.size();
	//이미지 데이터 불러오기
	for (idx = 0; idx < cnt; idx++) {
		//이미지 불러오기
		cv::Mat img = cv::imread(img_files[idx]);
		//이미지 불러오기 실패했을 경우
		if (img.empty()) ErrorMessage("Failed to load JPG files");
		//이미지 벡터의 넣기
		imgDatas.push_back(img);
	}

	//초기 윈도우 사이즈 설정
	cv::Size initSize(INIT_WIDTH, INIT_HEIGHT);
	//불러온 파일 이름의 윈도우 생성
	cv::namedWindow(windowTitle, cv::WINDOW_NORMAL);
	//생성된 윈도우 초기 사이즈 지정
	cv::resizeWindow(windowTitle, initSize);

	//슬라이드 상태 변수
	bool slideEnable = true;
	//윈도우 창 상태 변수
	bool wndfScreen = false;
	//idx 값 초기화
	idx = 0;

	while (slideEnable) {
		//벡터의 불러온 이미지 값 윈도우 적용
		cv::imshow(windowTitle, imgDatas[idx]);

		switch (cv::waitKey(TICK_TIME)) {
		case ESC:
			//while 문 종료 신호 설정
			slideEnable = false;
			break;
		case ENTER: {
			//윈도우 원래 속성 값 가져오기
			//auto oriProperty = cv::getWindowProperty(windowTitle, cv::WND_PROP_FULLSCREEN);
			//해당 윈도우 원래 속성은 WINDOW_NORMAL 이기에 직접 찍어서 쓰면됨

			//윈도우 상태 변경
			wndfScreen = !wndfScreen;

			//윈도우 속성 변경
			if (wndfScreen) {
				//전체화면
				cv::setWindowProperty(windowTitle, cv::WND_PROP_FULLSCREEN, cv::WINDOW_FULLSCREEN);
				//전체화면 아닐 경우
			}
			else {
				cv::setWindowProperty(windowTitle, cv::WND_PROP_FULLSCREEN, cv::WINDOW_NORMAL);
			}
		}
		default:
			//idx 값이 전체 이미지 개수를 넘으면 초기화
			if (++idx >= cnt) idx = 0;
		}
	}

	//윈도우 삭제
	cv::destroyAllWindows();

	return 0;
}