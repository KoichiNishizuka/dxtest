//zyouhouzikken
#include <DxLib.h>
#include <math.h>
#define PI 3.1415926f
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



int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);

	Fps fps;
	float vx = -5.0f, vy = 10.0f,vz= -5.0f, t = 0.0f;
	float x = 0, y = 1, z = 0, angle = 0, speed = 1;
	//int i, Grassllllow=0;
	//int Width, Height, GrHandle=0;
	 
	char box='S';
	byte buffer[] = { box };

	
	bool ini=false;

	int addi=0;
		 
	int  remain=5;
	int g = 0;
	int sleep = 0;//������Ƃ����҂Ƃ���
	float angleX = 0.f, angleY = 0.f;

	float r = 50.0f;//���a

	float tx = -10.0f;//������ς����x���̃^�[�Q�b�g���ς��

	float cx = tx, cy = 0.0f ,cz=r;
	
	int thy = 15;
	int thz = 15;
	//const char *String=0;
	//3D���f���̓ǂݍ���
	int Soccerball = MV1LoadModel("C:\\Users\\Angelic Angel\\source\\repos\\dxtest\\Soccer ball\\Soccer Ball Low.blend.x");
	int plane = MV1LoadModel("C:\\Users\\Angelic Angel\\source\\repos\\dxtest\\plane\\Plane.x");
	int Soccerfield = MV1LoadModel("C:\\Users\\Angelic Angel\\source\\repos\\dxtest\\soccer field\\Soccer Grount Base high optimised.blend.x");
	int Soccergoal = MV1LoadModel("C:\\Users\\Angelic Angel\\source\\repos\\dxtest\\Soccer goal\\goal low optimised.blend.x");
	
	//�T�b�J�[�{�[���̉摜�̓ǂݍ���
	int soccerHAndle = LoadGraph("C:\\Users\\Angelic Angel\\source\\repos\\dxtest\\soccerball.jpg");
	/*// ���f���Ɋ܂܂��e�N�X�`���̑������擾����
	Grassllllow = MV1GetTextureNum(Soccerfield);

	// �e�N�X�`���̐������J��Ԃ�
	for (i = 0; i < Grassllllow; i++)
	{
		// ��ʂ��N���A����
		ClearDrawScreen();

		// �e�N�X�`���̃O���t�B�b�N�n���h�����擾����
		GrHandle = MV1GetTextureGraphHandle(Soccerfield, i);

		
		// �e�N�X�`���̑傫����`�悷��
		GetGraphSize(GrHandle, &Width, &Height);
		DrawFormatString(0, 1, GetColor(255, 255, 255), "          %dx%d", Width, Height);

		
	}
		// �e�N�X�`����`�悷��
		DrawGraph(0, 1, GrHandle, TRUE);
		*/
		

	//�T�b�J�[�S�[������]
	MV1SetRotationXYZ(Soccergoal,VGet(90.0f* DX_PI_F / 180.0f, 90.0f * DX_PI_F / 180.0f, 0.0f));
	MV1SetRotationXYZ(Soccerfield, VGet(90.0f* DX_PI_F / 180.0f, 180.0f * DX_PI_F / 180.0f, 0.0f));
	
	//�T�b�J�[���Z��̊g��
	MV1SetScale(Soccerfield, VGet(7.0f, 7.0f, 7.0f));
	
	//���s0.1�`1000�܂ł��J�����̕`��͈͂Ƃ���
	SetCameraNearFar(0.01f, 100000.0f);

	/*while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen())
	{
         
	}*/
	//(x,y,z)�̎��_����(0,10,0)�̃^�[�Q�b�g������p�x�ɃJ������ݒu
	SetCameraPositionAndTarget_UpVecY(VGet(cx,cy, cz), VGet(tx, 0.0f, 0.0f));
	//SetCameraPositionAndTarget_UpVecY(VGet(0, 90, -15), VGet(0.0f, 0.0f, 0.0f));
	//SetCameraPositionAndTarget_UpVecY(VGet(30, 20, 0), VGet(10.0f, 10.0f, 0.0f));
	
	//���̓_��box=S;
	DrawFormatString(240, 300, GetColor(255, 255, 255), " X�L�[�������Ă�������");
	ScreenFlip();
	while (CheckHitKey(KEY_INPUT_X) != 1)
	{
		//if ((CheckHitKey(KEY_INPUT_X))) {
		//s = 'S';
		
		//}
		box = 'S';														//�o�C�g�^�ő������
	}
	buffer[0] = box;				//X�������烋�[�v������S������B
	ClearDrawScreen();


	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen()) {
		fps.Update();	//�X�V
		//ScreenFlip();
		fps.Wait();		//�ҋ@

		if (!ini) {
			addi = 0; sleep = 0; x = 0; y = 1; z = 0;
			angleX = 0.f; angleY = 0.f;
			t = 0;

			vx = -5.0f; vy = 10.0f; vz = 5.0;//�̂��̂����肩����炤�����̃��[�v�ɓ����K�v����B

		}

		// �w��ʒu�Ƀ��f����z�u
		MV1SetPosition(Soccerball, VGet(x, y, z));
		//MV1SetPosition(plane, VGet(0, 10, 0));
		MV1SetPosition(Soccerfield, VGet(1, 10.1, 1));
		MV1SetPosition(Soccergoal, VGet(-30, 0, 0));
		

		// �R�c���f���̕`��
		MV1DrawModel(Soccerball);
		//MV1DrawModel(plane);
		MV1DrawModel(Soccerfield);
		MV1DrawModel(Soccergoal);
		
		MV1SetRotationXYZ(Soccerball, VGet(angleX, angleY, 0.0f));

		if (!ini) {

		}
		for (int g = 0; g < remain; g++)
		{
			while (!ini)
			{

				ClearDrawScreen();
				x = 0;
				y = 1;
				z = 0; angleX = 0.f; angleY = 0.f;
				t = 0;
				vx = -5.0f; vy = 10.0f; vz = 5.0;

				if (CheckHitKey(KEY_INPUT_ESCAPE)) {
					ini = true;
					box = 'I';													//�o�C�g�^�ő������
					buffer[0] = box;
				}


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


				switch (g)
				{
				case 0:

					DrawFormatString(600, 20, GetColor(0, 0, 255), "�~5");
					//ScreenFlip();
					break;


				case 1:

					DrawFormatString(600, 20, GetColor(0, 0, 255), "�~4");
					//ScreenFlip();
					break;

				case 2:

					DrawFormatString(600, 20, GetColor(0, 0, 255), "�~3");
					//ScreenFlip();
					break;


				case 3:

					DrawFormatString(600, 20, GetColor(0, 0, 255), "�~2");
					//ScreenFlip();
					break;


				case 4:

					DrawFormatString(600, 20, GetColor(0, 0, 255), "�~1");
					//ScreenFlip();
					break;


				

				}
				
				


				// �w��ʒu�Ƀ��f����z�u
				MV1SetPosition(Soccerball, VGet(x, y, z));
				MV1SetPosition(plane, VGet(0, 10, 0));
				MV1SetPosition(Soccerfield, VGet(1, 10.1, 1));
				MV1SetPosition(Soccergoal, VGet(-30, 0, 0));
				
				// �R�c���f���̕`��
				MV1DrawModel(Soccerball);
				//MV1DrawModel(plane);
				MV1DrawModel(Soccerfield);
				MV1DrawModel(Soccergoal);
				
				DrawFormatString(240, 300, GetColor(255, 255, 255), "Esc�L�[�������Ă�������");

				DrawFormatString(50, 50, GetColor(255, 255, 255), "%3f.4,%3f.4,%3f.4", cx, cy, cz);

				SetCameraPositionAndTarget_UpVecY(VGet(cx, cy, cz), VGet(tx, 0.0f, 0.0f));
				DrawExtendGraph(590, 20, 590 - 50, 20 + 50, soccerHAndle, FALSE);
				ScreenFlip();
				Sleep(100);

			}

			//�����Ń{�[��������O�ɉ����x�̏�����

			while (ini)
			{
				fps.Update();	//�X�V
		   //ScreenFlip();
				fps.Wait();		//�ҋ@

				ClearDrawScreen();
				// �w��ʒu�Ƀ��f����z�u
				MV1SetPosition(Soccerball, VGet(x, y, z));
				//MV1SetPosition(plane, VGet(0, 10, 0));
				MV1SetPosition(Soccerfield, VGet(1, 10.1, 1));
				MV1SetPosition(Soccergoal, VGet(-30, 0, 0));

				// �R�c���f���̕`��
				MV1DrawModel(Soccerball);
				//MV1DrawModel(plane);
				MV1DrawModel(Soccerfield);
				MV1DrawModel(Soccergoal);
				

				MV1SetRotationXYZ(Soccerball, VGet(angleX, angleY, 0.0f));
				
				if (sleep > 120) {//��b�҂��Ă��灨fps���`���鎞��
					t += 1.0f / fps.mFps;

					if (x > -28) {	//�S�[���ɂ������̏���
						x += vx * (1.0f / fps.mFps);
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
					if (y >= 1)	//�n�ʂ����������̏���

						y = vy * t - 0.2f*G*t*t + 1.0f;

					else {

						if (vx <= 0) {
							vx = 0.998f*vx;

						}
					}
					if (x <= -20.4)
					{
						//�S�[���|�X�g�̔���
						if (/*x >= -20.4 && y < 11 && z <= 10.4 && z >= 9.6 ||*/ x >= -20.4 &&x <= -20.3&& y < 11/* && z >= -10.4&&z <= -9.6 /*|| x >= -20.4 && y <11 && y>10 && -10.4 <= z <= 10.4*/)
						{
							x -= vx * (1.0f / fps.mFps);
							DrawFormatString(50, 50, GetColor(255, 255, 255), "reflect");
						}

						addi++;
						if (y <= 10 && z >= -9.6 && 9.6 >= z) {
							DrawFormatString(50, 50, GetColor(255, 255, 255), "GOAL!!!!!!!!");
							//con = 'CON';
							if (addi == 1) {
								box = 'G';												//�o�C�g�^�ő������
								buffer[0] = box;
							}

							if (addi > 300) {
								ini = false;
								addi = 0;
								sleep = 0;
							}

						}

						else
						{
							DrawFormatString(50, 50, GetColor(255, 255, 255), "m9(^�D^)�߷ެ�");
							if (addi == 1) {
								box = 'O';												//�o�C�g�^�ő������
								buffer[0] = box;
							}

							if (addi > 300) {
								ini = false;
								addi = 0;
								sleep = 0;
							}
						}



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
