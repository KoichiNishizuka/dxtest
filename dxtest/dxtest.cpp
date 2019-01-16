//zyouhouzikken
#include <DxLib.h>
#include <math.h>
#include <vector>
#include "serial.h"
#define PI 3.1415926f
union
{
	float data;
	byte binaly[4];
}vvx;
union
{
	float data;
	byte binaly[4];
}vvy;
union
{
	float data;
	byte binaly[4];
}vvz;

static int readResult;

const float G = 9.8f;

class Fps {

public:
	int mStartTime;         //����J�n����
	int mCount;             //�J�E���^
	float mFps;             //fps
	static const int N = 60;//���ς����T���v����
	static const int FPS = 60;	//�ݒ肵��FPS


	Fps() {
		mStartTime = 0;
		mCount = 0;
		mFps = 0;

	}

	bool Update() {
		if (mCount == 0) { //1�t���[���ڂȂ玞�����L��      
			mStartTime = GetNowCount();
		}
		if (mCount == N) { //60�t���[���ڂȂ畽�ς��v�Z����
			int t = GetNowCount();
			mFps = 1000.f / ((t - mStartTime) / (float)N);
			mCount = 0;
			mStartTime = t;
		}
		mCount++;
		return true;
	}

	void Draw() {
		DrawFormatString(0, 0, GetColor(255, 255, 255), "%.1f", mFps);
	}

	void Wait() {
		int tookTime = GetNowCount() - mStartTime;	//������������
		int waitTime = mCount * 1000 / FPS - tookTime;	//�҂ׂ�����
		if (waitTime > 0) {
			Sleep(waitTime);	//�ҋ@
		}
	}
};

static const float ROTATE_SPEED = DX_PI_F / 90;//��]�X�s�[�h

float Dice(void) {
	int res = 0;
	res = rand() % 8 + 1;
	return (float)res;
}


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);

	auto list = getSerialList();
	Serial kicker;
	Serial keeper;

	Fps fps;
	float vx = -5.0f, vy = 10.0f,vz= -5.0f, t = 0.0f;
	float x = -28.0f, y = 0, z = 0, angle = 0, speed = 1;
	int  Grassllllow=0;
	readResult = 0;
	int ovx = 0, ovy = 0, ovz = 0;
	 
	unsigned char box='S';

	byte writebuffer[1] = {};
	byte readbuffer[30] = {};

	
	bool ini=false;
	bool ref = true;

	int addi=0;
		 
	int  remain=5;
	int g = 0;
	int sleep = 0;//������Ƃ����҂Ƃ���
	float angleX = 0.f, angleY = 0.f;

	float r = 10.0f;//���a

	float tx = -30.0f;//������ς����x���̃^�[�Q�b�g���ς��

	float cx = tx, cy = 0.0f ,cz=r;
	
	int thy = 15;
	int thz = 15;
	float dz = 6.0f / 256.0f;
	float dy = 3.1f / 256.0f;
	float hz, hy = 0.0f;

	int AttachIndex;
	float TotalTime, PlayTime;

	BOOL kickaction = FALSE;
	const char *String=0;



	//3D���f���̓ǂݍ���
	int Soccerball = MV1LoadModel("C:\\Users\\Angelic Angel\\source\\repos\\dxtest\\Soccer ball\\Soccer Ball Low.blend.x");
	//int plane = MV1LoadModel("C:\\Users\\Angelic Angel\\source\\repos\\dxtest\\plane\\Plane.x");
	int Soccerfield = MV1LoadModel("C:\\Users\\Angelic Angel\\source\\repos\\dxtest\\soccer field\\Soccer Grount Base high optimised.blend.x");
	int Soccergoal = MV1LoadModel("C:\\Users\\Angelic Angel\\source\\repos\\dxtest\\Soccer goal\\goal low optimised.blend.x");
	int Soccerman = MV1LoadModel("C:\\Users\\Angelic Angel\\source\\repos\\dxtest\\Soccer man low polygon riged animeblend.mv1");
	int Soccerkeeper= MV1LoadModel("C:\\Users\\Angelic Angel\\source\\repos\\dxtest\\soccer keeper\\Soccer man Hand only.blend.x");

	//�T�b�J�[�{�[���̉摜�̓ǂݍ���
	int soccerHAndle = LoadGraph("C:\\Users\\Angelic Angel\\source\\repos\\dxtest\\soccerball.jpg");
	
	int ground_tex_handle = LoadGraph("../soccer field/Soccer Grount Base high Grassllllow.png");
	MV1SetTextureGraphHandle(Soccerfield, 0, ground_tex_handle, TRUE);
	
	SetLightEnable(FALSE);
	SetGlobalAmbientLight(GetColorF(0.000f, 0.000f, 0.000f, 0.0f));

	int Light0Handle = CreatePointLightHandle(VGet(0.000f, 0.000f, -0.458f), 2000.000f, 1.000f, 0.000f, 0.000f);
	SetLightDifColorHandle(Light0Handle, GetColorF(1.000f, 1.000f, 1.000f, 1.000f));
	SetLightSpcColorHandle(Light0Handle, GetColorF(0.414f, 0.414f, 0.414f, 0.000f));
	SetLightAmbColorHandle(Light0Handle, GetColorF(0.000f, 0.000f, 0.000f, 0.000f));

	int Light1Handle = CreatePointLightHandle(VGet(-0.916f, 0.000f, -3.207f), 36.652f, 1.000f, 0.000f, 0.000f);
	SetLightDifColorHandle(Light1Handle, GetColorF(1.000f, 1.000f, 1.000f, 0.000f));
	SetLightSpcColorHandle(Light1Handle, GetColorF(0.859f, 0.859f, 0.859f, 0.000f));
	SetLightAmbColorHandle(Light1Handle, GetColorF(0.000f, 0.000f, 0.000f, 0.000f));

	int Light2Handle = CreateDirLightHandle(VGet(-0.322f, -0.294f, 0.900f));
	SetLightDifColorHandle(Light2Handle, GetColorF(1.000f, 1.000f, 1.000f, 1.000f));
	SetLightSpcColorHandle(Light2Handle, GetColorF(0.500f, 0.500f, 0.500f, 0.000f));
	SetLightAmbColorHandle(Light2Handle, GetColorF(0.000f, 0.000f, 0.000f, 0.000f));






	//�T�b�J�[�S�[������]
	MV1SetRotationXYZ(Soccergoal,VGet(90.0f* DX_PI_F / 180.0f, 90.0f * DX_PI_F / 180.0f, 0.0f));
	MV1SetRotationXYZ(Soccerfield, VGet(0.0f,0.0f,0.0f));
	MV1SetRotationXYZ(Soccerkeeper, VGet(0.0f, 3 * DX_PI_F / 2, 0.0f));
	
	//�T�b�J�[���Z��̊g��
	MV1SetScale(Soccerfield, VGet(9.0f, 9.0f, 9.0f));
	MV1SetScale(Soccergoal, VGet(0.3f, 0.3f, 0.3f));
	MV1SetScale(Soccerkeeper, VGet(0.7f, 0.7f, 0.7f));

	//�L�b�J�[���f���̏k��
	MV1SetScale(Soccerman, VGet(0.0025f, 0.0025f, 0.0025f));
	MV1SetScale(Soccerball, VGet(0.2f, 0.2f, 0.2f));
	//�L�b�J�[���f���̉�]
	MV1SetRotationXYZ(Soccerman, VGet(0.0f,-90.0f * DX_PI_F / 180.0f, 0.0f));
	//���s0.1�`1000�܂ł��J�����̕`��͈͂Ƃ���
	SetCameraNearFar(0.01f, 100000.0f);

	
	//(x,y,z)�̎��_����(0,10,0)�̃^�[�Q�b�g������p�x�ɃJ������ݒu
	SetCameraPositionAndTarget_UpVecY(VGet(cx,cy, cz), VGet(tx, 0.0f, 0.0f));
	//SetCameraPositionAndTarget_UpVecY(VGet(0, 90, -15), VGet(0.0f, 0.0f, 0.0f));
	//SetCameraPositionAndTarget_UpVecY(VGet(0,1000, 0), VGet(0.0f, 0.0f, 0.0f));
	
	//���̓_��box=S;
	//DrawFormatString(240, 300, GetColor(255, 255, 255), " X�L�[�������Ă�������");
	ScreenFlip();
	//if (box) {
		//s = 'S';
		
		//}


		box = 'S';
		writebuffer[0] = box;				//X�������烋�[�v������S������B
		//kicker.write(&box, 1);//S����܂����O�O
		//keeper.write(&box, 1);
		//if(box=='S')
		//�o�C�g�^�ő������
		/*int readResult = serial->readSerialPort(`byte(char)�^�̔z��`,`�z��̗v�f��`); //���킾��readResult��0����������
		print("%s", `byte(char)�^�̔z��`)
		serial->writeSerialPort(`byte(char)�^�̔z��`,`�z��̗v�f��`); 
		*/
		/*while(!kicker.isOpened() || !keeper.isOpened())
		{
			for (const auto info : list)
			{
				if (!kicker.isOpened())
				{
					if (kicker.open(info))
					{
						unsigned char c = 'S';
						kicker.write(&c, 1);
						auto v = kicker.read();
						if (v[0] != 'k')
						{
							kicker.close();
						}
					}
				}
				if (!keeper.isOpened())
				{
					if (keeper.open(info))
					{
						unsigned char c = 'S';
						keeper.write(&c, 1);
						auto v = keeper.read();
						if (v[0] != 'K')
						{
							keeper.close();
						}
					}
				}
			}
		}*/
		DrawFormatString(10, 10, GetColor(255, 0, 0), "k��M���A���݂̃X�e�[�g��%c�ł�", box);
		//print("%s", `byte(char)�^�̔z��`);

		/*if (CheckHitKey(KEY_INPUT_K)) {//�{�Ԃł͏���
			box = 'k';
		}*/

		ScreenFlip();
		ClearDrawScreen();
	

	box = 'I';
	writebuffer[0] = box;
	

	ClearDrawScreen();
	
	AttachIndex = MV1AttachAnim(Soccerman,0,-1,FALSE);
	TotalTime = MV1GetAttachAnimTotalTime(Soccerman, AttachIndex);
	PlayTime = 0.0f;


	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen()) {
		fps.Update();	//�X�V
		//ScreenFlip();
		fps.Wait();		//�ҋ@

		if (!ini) 
		{
			addi = 0; sleep = 0; x = -28.0f; y = 0; z = 0;
			angleX = 0.f; angleY = 0.f;
			t = 0;
			PlayTime = 0.0f;
			vx = 0; vy = 0; vz = 0;

			//vx = -5.0f; vy = 10.0f; vz = 5.0;//�̂��̂����肩����炤�����̃��[�v�ɓ����K�v����B

		}

		// �w��ʒu�Ƀ��f����z�u
		MV1SetPosition(Soccerball, VGet(x, y, z));
		//MV1SetPosition(plane, VGet(0, 10, 0));
		MV1SetPosition(Soccerfield, VGet(0, 12.5, 0));
		MV1SetPosition(Soccergoal, VGet(-42, 0, 0));
		MV1SetPosition(Soccerman, VGet(-25, 0, 0));
		MV1SetPosition(Soccerkeeper, VGet(-39.0f, 1.5f, 0.0f));

		// �R�c���f���̕`��
		MV1DrawModel(Soccerball);

		//MV1DrawModel(plane);
		MV1DrawModel(Soccerfield);
		MV1DrawModel(Soccergoal);
		
		MV1SetRotationXYZ(Soccerball, VGet(angleX, angleY, 0.0f));

		for (int g = 0; g < remain; g++)
		{
			while (!ini)
			{

				ClearDrawScreen();
				while (box != 'O') {
					/*kicker.write(&box, 1);
					if (kicker.available() > 0)
					{
						auto readResult = kicker.read(); //���킾��readResult��0����������
						box = readResult[0];
					}*/
					if (CheckHitKey(KEY_INPUT_O)) {
						box = 'O';
					}

					// �w��ʒu�Ƀ��f����z�u
					MV1SetPosition(Soccerball, VGet(x, y, z));
					//MV1SetPosition(plane, VGet(0, 10, 0));
					MV1SetPosition(Soccerfield, VGet(0, 12.5, 0));
					MV1SetPosition(Soccergoal, VGet(-42, 0, 0));
					MV1SetPosition(Soccerman, VGet(-25, 0, 0));


					// �R�c���f���̕`��
					MV1DrawModel(Soccerball);

					//MV1DrawModel(plane);
					MV1DrawModel(Soccerfield);
					MV1DrawModel(Soccergoal);

					MV1SetRotationXYZ(Soccerball, VGet(angleX, angleY, 0.0f));

					MV1SetAttachAnimTime(Soccerman, AttachIndex, PlayTime);
					MV1DrawFrame(Soccerman, 127);

					DrawFormatString(10, 10, GetColor(255, 0, 0), "O���������s���Ă��������B�X�e�[�g:%c", box);

					ScreenFlip();
					ClearDrawScreen();
				}
				ClearDrawScreen();
				if(CheckHitKey(KEY_INPUT_ESCAPE)){

					box = 'R';
					writebuffer[0] = box;
					/*kicker.write(&box, 1);
					keeper.write(&box, 1);*/
					bool sendFlag = false;
					/*while (!sendFlag) {
						if (kicker.available() >= 12)
						{
							auto readResult = kicker.read(); 

							if (readResult.size() >= 12) { sendFlag = true; }
							//print("%s", `byte(char)�^�̔z��`)

							vvx.binaly[0] = readResult[3];
							vvx.binaly[1] = readResult[2];
							vvx.binaly[2] = readResult[1];
							vvx.binaly[3] = readResult[0];
							//vvx.data = (vvx.binaly[3] << 24) | (vvx.binaly[2] << 16) | (vvx.binaly[1] << 8) | (vvx.binaly[0]);
							vvy.binaly[0] = readResult[7];
							vvy.binaly[1] = readResult[6];
							vvy.binaly[2] = readResult[5];
							vvy.binaly[3] = readResult[4
							];
							//vvy.data = (vvy.binaly[3] << 24) | (vvy.binaly[2] << 16) | (vvy.binaly[1] << 8) | (vvy.binaly[0]);

							vvz.binaly[0] = readResult[11];
							vvz.binaly[1] = readResult[10];
							vvz.binaly[2] = readResult[9];
							vvz.binaly[3] = readResult[8];
						}
						//vvz.data = (vvz.binaly[3] << 24) | (vvz.binaly[2] << 16) | (vvz.binaly[1] << 8) | (vvz.binaly[0]);
						
						/*if (CheckHitKey(KEY_INPUT_R)) {//�{�Ԃł͏���
							box = 12;
						}*/

						// �w��ʒu�Ƀ��f����z�u
						/*MV1SetPosition(Soccerball, VGet(x, y, z));
						//MV1SetPosition(plane, VGet(0, 10, 0));
						MV1SetPosition(Soccerfield, VGet(0, 12.5, 0));
						MV1SetPosition(Soccergoal, VGet(-42, 0, 0));
						MV1SetPosition(Soccerman, VGet(-25, 0, 0));

						// �R�c���f���̕`��
						MV1DrawModel(Soccerball);

						//MV1DrawModel(plane);
						MV1DrawModel(Soccerfield);
						MV1DrawModel(Soccergoal);

						MV1SetRotationXYZ(Soccerball, VGet(angleX, angleY, 0.0f));

						MV1SetAttachAnimTime(Soccerman, AttachIndex, PlayTime);
						MV1DrawFrame(Soccerman, 127);

						DrawFormatString(10, 10, GetColor(255, 0, 0), "R���x����M���ł��B");


						ScreenFlip();
						ClearDrawScreen();
					}*/
					ini = true;
					/*DrawFormatString(10, 10, GetColor(255, 0, 0), "%f %f %f", vvx.data, vvy.data, vvz.data);
					ScreenFlip();
					Sleep(5000);
					ClearDrawScreen();*/
				}
				x = -28.0f;
				y = 0;
				z = 0; angleX = 0.f; angleY = 0.f;
				t = 0;
				float power = 1.0f;
				//power=**;
				//vx = vvx.data; vy = vvy.data; vz = vvz.data;
				vx = -1.0f*Dice(); vy =Dice(); vz = 0/*Dice()-Dice()*/;
				PlayTime = 0.0f;
				kickaction = FALSE;
				ref = true;

				/*if (box=='O') {
					ini = true;
					box = 'I';													//�o�C�g�^�ő������
					buffer[0] = box;
					box = buffer[0];
					//print("%s", `byte(char)�^�̔z��`);

				}*/


				if (CheckHitKey(KEY_INPUT_RIGHT)) {
					ClearDrawScreen();

					thy += 15;
					if (thy <= 180) {
						cz = r * (cos((float)thz*(PI / 180.0f))*sin((float)thy*(PI / 180.0f)));
						cx = r * (cos((float)thz*(PI / 180.0f))*cos((float)thy*(PI / 180.0f))) + tx;
					}
					else {
						thy = 180;
					}
				}
				else if (CheckHitKey(KEY_INPUT_LEFT)) {
					ClearDrawScreen();
					thy -= 15;
					if (thy >= -180) {
						cz = r * (cos((float)thz*(PI / 180.0f))*sin((float)thy*(PI / 180.0f)));
						cx = r * (cos((float)thz*(PI / 180.0f))*cos((float)thy*(PI / 180.0f))) + tx;
					}
					else {
						thy = -180;
					}

				}

				if (CheckHitKey(KEY_INPUT_UP)) {
					ClearDrawScreen();
					thz += 15;

					if (thz <= 90) {


						cy = r * (sin((float)thz*(PI / 180.0f)));
						cz = r * (cos((float)thz*(PI / 180.0f))*sin((float)thy*(PI / 180.0f)));
						cx = r * (cos((float)thz*(PI / 180.0f))*cos((float)thy*(PI / 180.0f))) + tx;
						//cx = 30 * (cos((float)thz*(PI / 180.0f))) - 21.0f;
					}
					else {
						thz = 90;
					}
				}
				else if (CheckHitKey(KEY_INPUT_DOWN)) {
					ClearDrawScreen();
					thz -= 15;

					if (thz >= 0) {

						cy = r * (sin((float)thz*(PI / 180.0f)));
						cz = r * (cos((float)thz*(PI / 180.0f))*sin((float)thy*(PI / 180.0f)));
						cx = r * (cos((float)thz*(PI / 180.0f))*cos((float)thy*(PI / 180.0f))) + tx;
						//cx = 30 * (cos((float)thz*(PI / 180.0f))) - 21.0f;
					}
					else {
						thz = 0;
					}
				}

				//�{�[���̎c�@�\��
				switch (g)
				{
				case 0:

					DrawFormatString(600, 20, GetColor(0, 0, 255), "�~5");
					
					break;


				case 1:

					DrawFormatString(600, 20, GetColor(0, 0, 255), "�~4");
					
					break;

				case 2:

					DrawFormatString(600, 20, GetColor(0, 0, 255), "�~3");
					
					break;


				case 3:

					DrawFormatString(600, 20, GetColor(0, 0, 255), "�~2");
					
					break;

				case 4:

					DrawFormatString(600, 20, GetColor(0, 0, 255), "�~1");
				
					break;
				}
				
				hz = 0.0f;
				hy = 1.5f;


				// �w��ʒu�Ƀ��f����z�u
				MV1SetPosition(Soccerball, VGet(x, y, z));
				//MV1SetPosition(plane, VGet(0, 10, 0));
				MV1SetPosition(Soccerfield, VGet(0, 12.5, 0));
				MV1SetPosition(Soccergoal, VGet(-42, 0, 0));
				MV1SetPosition(Soccerman, VGet(-25, 0, 0));
				MV1SetPosition(Soccerkeeper, VGet(-39.0f, 1.5f, 0.0f));

				// �R�c���f���̕`��
				MV1DrawModel(Soccerball);
				//MV1DrawModel(plane);
				MV1DrawModel(Soccerfield);
				MV1DrawModel(Soccergoal);
				MV1SetAttachAnimTime(Soccerman, AttachIndex, PlayTime);
				MV1DrawFrame(Soccerman,127);
				MV1DrawModel(Soccerkeeper);
				DrawFormatString(240, 300, GetColor(255, 255, 255), "Esc�L�[�������Ă�������(�����L�[�ŃJ�����̈ʒu��ς�����B)");

				DrawFormatString(50, 50, GetColor(255, 255, 255), "%3f.4,%3f.4,%3f.4", cx, cy, cz);

				SetCameraPositionAndTarget_UpVecY(VGet(cx, cy, cz), VGet(tx, 0.0f, 0.0f));
				//�T�b�J�[�{�[���c�@�\��
				DrawExtendGraph(590, 20, 590 - 20, 20 + 20, soccerHAndle, FALSE);
				ScreenFlip();
				Sleep(100);

			}

			//�����Ń{�[��������O�ɉ����x�̏�����
			hy = 1.5f;
			hz = 0.0f;
			while (ini)
			{
				fps.Update();	//�X�V
		   //ScreenFlip();
				fps.Wait();		//�ҋ@


				int8_t z_bun = 0;
				uint8_t y_bun = 0;
				/*if (keeper.available() > 1)
				{
					auto pos = keeper.read();
					z_bun = pos[0];
					y_bun = pos[1];
				}*/
				z_bun = (float)(rand() % 256 - 128);
				y_bun = (float)(rand() % 256);
				hz = dz * z_bun;
				hy = dy * y_bun;
				
				/*if (CheckHitKey(KEY_INPUT_UP))
				{
					hy += dy;
				}
				if(CheckHitKey(KEY_INPUT_DOWN))
				{
					hy -= dy;
				}
				if(CheckHitKey(KEY_INPUT_LEFT))
				{
					hz -= dz;
				}
				if(CheckHitKey(KEY_INPUT_RIGHT))
				{
					hz += dz;
				}*/
				ClearDrawScreen();
				// �w��ʒu�Ƀ��f����z�u
				MV1SetPosition(Soccerball, VGet(x, y, z));
				MV1SetPosition(Soccerfield, VGet(0, 12.5, 0));
				MV1SetPosition(Soccergoal, VGet(-42, 0, 0));
				MV1SetPosition(Soccerman, VGet(-25, 0,0));
				MV1SetPosition(Soccerkeeper, VGet(-39.0f, hy, hz));
				if (PlayTime <= TotalTime)
				{
					//PlayTime += (1.0f / fps.mFps) * 30;
					PlayTime += (1.0f / 60.0f) * 30;
					if (PlayTime >= TotalTime-10.0f)
						
					{
						//PlayTime = 0.0f;
						kickaction = TRUE;
					}
					MV1SetAttachAnimTime(Soccerman, AttachIndex, PlayTime);
				}
				// �R�c���f���̕`��
				MV1DrawModel(Soccerball);
				//MV1DrawModel(plane);
				MV1DrawModel(Soccerfield);
				MV1DrawModel(Soccergoal);
				MV1DrawFrame(Soccerman, 127);
				MV1DrawModel(Soccerkeeper);
				MV1SetRotationXYZ(Soccerball, VGet(angleX, angleY, 0.0f));
				
				if (kickaction) {//��b�҂��Ă��灨fps���`���鎞��
					//t += 1.0f / fps.mFps;
					t += 1.0f / 60.0f;
					if (t > 10) { ini = false; }

					if (x > -41.8) {	//�S�[���ɂ������̏���
						x += vx * (1.0f / fps.mFps);
						z += vz * (1.0f / fps.mFps);
						angleX -= ROTATE_SPEED;
						if (CheckHitKey(KEY_INPUT_Z))
						{
							//if (z > -9 && z < 9)
							z += vz * (1.0f / fps.mFps);
							angleY += 0.99f*ROTATE_SPEED;
						}
						if (CheckHitKey(KEY_INPUT_C))
						{
							//if(z>-9&&z<9)
							z -= vz * (1.0f / fps.mFps);
							angleY += 0.99f*ROTATE_SPEED;
						}
					}
					if (y >= 0)	//�n�ʂ����������̏���

						y = vy * t - 0.4f*G*t*t + 1.0f;

					else {

							vx = 0.998f*vx;
							vz = 0.998f*vz;
					}

					if (x <= -39 && x>=-39.3)
					{
						if (y >= hy - 0.3 && y <= hy + 0.3 && z >= hz - 0.3 && z <= hz + 0.3)
						{
							vx = -vx;
						}
					}

					if (x <= -39.5)
					{
						addi++;
					
						if (y <= 3.1 && z >= -3.0 && 3.0 >= z) {
							DrawFormatString(50, 50, GetColor(255, 255, 255), "GOAL!!!!!!!!");
							//con = 'CON';
							if (addi == 1) {
								box = 'G';												//�o�C�g�^�ő������
								readbuffer[0] = box;
							}
						}
						//�S�[���|�X�g�̔���
						else if (y<3.5 && z <=3.5&& z >3.0 || y < 3.5 && ref && z >= -3.5&&z < -3.0 || y < 3.5 && y>3.1 && -3.5 <= z && z <=3.5)
						{
							vx = -vx;
							ref = false;
							DrawFormatString(50, 50, GetColor(255, 255, 255), "m9(^�D^)�߷ެ�");
							if (addi == 1) {
								box = 'F';												//�o�C�g�^�ő������
								readbuffer[0] = box;
							}

						}
						
						else
						{
							DrawFormatString(50, 50, GetColor(255, 255, 255), "m9(^�D^)�߷ެ�");
							if (addi == 1) {
								box = 'F';												//�o�C�g�^�ő������
								readbuffer[0] = box;
							}

						}
						/*if (addi > 300) {
							ini = false;
							addi = 0;
							sleep = 0;
						}*/
					}
					else if (vx<vvx.data*0.55) {
						DrawFormatString(50, 50, GetColor(255, 255, 255), "m9(^�D^)�߷ެ�");
						if (addi == 1) {
							box = 'F';												//�o�C�g�^�ő������
							readbuffer[0] = box;
							addi += 120;
						}
					}
					if (box == 'G' || box == 'F') {
						addi++;
						switch (box) {


						case'F':DrawFormatString(50, 50, GetColor(255, 255, 255), "m9(^�D^)�߷ެ�");
							break;

						case'G':DrawFormatString(50, 50, GetColor(255, 255, 255), "GOAL!!!!!!!!");
							break;

						}
					}

					if (addi > 300) {
						ini = false;
						addi = 0;
						sleep = 0;
					}
				}

				else {
					sleep++;//�J�E���g����
				}

				DrawFormatString(0, 0, GetColor(255, 255, 255), "x=%.1f y=%.1f z=%.1f", x, y, z);
				DrawFormatString(0, 20, GetColor(255, 255, 255), "%.1f", fps.mFps);

				

				//DrawFormatString(50, 50, GetColor(255, 255, 255), "%3f.4,%3f.4,%3f.4", cx, cy, cz);

				SetCameraPositionAndTarget_UpVecY(VGet(cx, cy, cz), VGet(tx, 0.0f, 0.0f));

				ScreenFlip();
			}
		}
	}
	DxLib_End();
	return 0;
}

