#include "DxLib.h"
#include "WindowData.h"

int fpsTime[2] = { 0, }, count = 0;
double fps = 0.0;

//fps��\�����邾��
void FpsFunction() {
	if (count == 0)
		fpsTime[0] = GetNowCount();						    //1���ڂ̎��Ԏ擾
	if (count == 59) {
		fpsTime[1] = GetNowCount();							//60���ڂ̎��Ԏ擾
		fps = 1000.0f / ((fpsTime[1] - fpsTime[0]) / 60.0f);//���肵���l����fps���v�Z
		count = 0;										//�J�E���g��������
	}
	else count++;	//���݉����ڂ��J�E���g
	if (fps != 0) DrawFormatString(window.WINDOW_WIDTH - 80, 0, GetColor(255, 125, 255), "fps %.1f", fps); //fps��\��
	return;
}


//hanoi