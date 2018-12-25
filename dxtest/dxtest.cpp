#include <DxLib.h>
#include <math.h>
#define PI 3.1415926f
const float G = 9.8f;
class Fps {

public:
	int mStartTime;         //測定開始時刻
	int mCount;             //カウンタ
	float mFps;             //fps
	static const int N = 60;//平均を取るサンプル数
	static const int FPS = 60;	//設定したFPS


	Fps() {
		mStartTime = 0;
		mCount = 0;
		mFps = 0;
	}

	bool Update() {
		if (mCount == 0) { //1フレーム目なら時刻を記憶
			mStartTime = GetNowCount();
		}
		if (mCount == N) { //60フレーム目なら平均を計算する
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
		int tookTime = GetNowCount() - mStartTime;	//かかった時間
		int waitTime = mCount * 1000 / FPS - tookTime;	//待つべき時間
		if (waitTime > 0) {
			Sleep(waitTime);	//待機
		}
	}
};

static const float ROTATE_SPEED = DX_PI_F / 90;//回転スピード



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
		 
	int  remain=6;

	int sleep = 0;//ちょっとだけ待とうか
	float angleX = 0.f, angleY = 0.f;

	float r = 50.0f;//半径

	float tx = -10.0f;//ここを変えればx軸のターゲットが変わる

	float cx = tx, cy = 0.0f ,cz=r;
	
	int thy = 15;
	int thz = 15;
	//const char *String=0;
	//3Dモデルの読み込み
	int Soccerball = MV1LoadModel("C:\\Users\\Angelic Angel\\source\\repos\\dxtest\\Soccer ball\\Soccer Ball Low.blend.x");
	int plane = MV1LoadModel("C:\\Users\\Angelic Angel\\source\\repos\\dxtest\\plane\\Plane.x");
	int Soccerfield = MV1LoadModel("C:\\Users\\Angelic Angel\\source\\repos\\dxtest\\soccer field\\Soccer Grount Base high optimised.blend.x");
	int Soccergoal = MV1LoadModel("C:\\Users\\Angelic Angel\\source\\repos\\dxtest\\Soccer goal\\goal low optimised.blend.x");
	int Soccerballx = MV1LoadModel("C:\\Users\\Angelic Angel\\source\\repos\\dxtest\\Soccer ball\\Soccer Ball Low.blend.x");
	/*// モデルに含まれるテクスチャの総数を取得する
	Grassllllow = MV1GetTextureNum(Soccerfield);

	// テクスチャの数だけ繰り返し
	for (i = 0; i < Grassllllow; i++)
	{
		// 画面をクリアする
		ClearDrawScreen();

		// テクスチャのグラフィックハンドルを取得する
		GrHandle = MV1GetTextureGraphHandle(Soccerfield, i);

		
		// テクスチャの大きさを描画する
		GetGraphSize(GrHandle, &Width, &Height);
		DrawFormatString(0, 1, GetColor(255, 255, 255), "          %dx%d", Width, Height);

		
	}
		// テクスチャを描画する
		DrawGraph(0, 1, GrHandle, TRUE);
		*/
		

	//サッカーゴールを回転
	MV1SetRotationXYZ(Soccergoal,VGet(90.0f* DX_PI_F / 180.0f, 90.0f * DX_PI_F / 180.0f, 0.0f));
	MV1SetRotationXYZ(Soccerfield, VGet(90.0f* DX_PI_F / 180.0f, 180.0f * DX_PI_F / 180.0f, 0.0f));
	
	//サッカー競技場の拡大
	MV1SetScale(Soccerfield, VGet(7.0f, 7.0f, 7.0f));
	
	//奥行0.1～1000までをカメラの描画範囲とする
	SetCameraNearFar(0.01f, 100000.0f);

	/*while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen())
	{
         
	}*/
	//(x,y,z)の視点から(0,10,0)のターゲットを見る角度にカメラを設置
	SetCameraPositionAndTarget_UpVecY(VGet(cx,cy, cz), VGet(tx, 0.0f, 0.0f));
	//SetCameraPositionAndTarget_UpVecY(VGet(0, 90, -15), VGet(0.0f, 0.0f, 0.0f));
	//SetCameraPositionAndTarget_UpVecY(VGet(30, 20, 0), VGet(10.0f, 10.0f, 0.0f));
	
	//この点でbox=S;
	DrawFormatString(240, 240, GetColor(255, 255, 255), " Xキーを押してください");
	ScreenFlip();
	while (CheckHitKey(KEY_INPUT_X) != 1)
	{
		//if ((CheckHitKey(KEY_INPUT_X))) {
		//s = 'S';
		
		//}
		box = 'S';														//バイト型で送るもの
	}
	buffer[0] = box;				//X押したらループ抜けてSが入る。
	ClearDrawScreen();


	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen()) {
		fps.Update();	//更新
		//ScreenFlip();
		fps.Wait();		//待機

		if (!ini) {
			addi = 0; sleep = 0; x = 0; y = 1; z = 0;
			angleX = 0.f; angleY = 0.f;
			t = 0;
			
			vx = -5.0f; vy = 10.0f; vz = 5.0;//のちのち相手からもらう部分のループに入れる必要あり。

		}

		// 指定位置にモデルを配置
		MV1SetPosition(Soccerball, VGet(x, y, z));
		MV1SetPosition(plane, VGet(0, 10, 0));
		MV1SetPosition(Soccerfield, VGet(1, 10.1, 1));
		MV1SetPosition(Soccergoal, VGet(-30, 0, 0));

		// ３Ｄモデルの描画
		MV1DrawModel(Soccerball);
		//MV1DrawModel(plane);
		MV1DrawModel(Soccerfield);
		MV1DrawModel(Soccergoal);

		MV1SetRotationXYZ(Soccerball, VGet(angleX, angleY, 0.0f));

		if (!ini) {

		}

		while (!ini)
		{

			ClearDrawScreen();
			if (CheckHitKey(KEY_INPUT_ESCAPE)) {
				ini = true;
				box = 'I';													//バイト型で送るもの
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

			for (int g = 0; g < remain; g++)
			{
				switch (g = 0)
				{
					MV1SetPosition(Soccerballx, VGet(290, 290, 0));
					MV1DrawModel(Soccerballx);
					DrawFormatString(300, 300, GetColor(255, 255, 255), "×５");
					break;
				}
				switch (g = 1)
				{
					MV1SetPosition(Soccerballx, VGet(290, 290, 0));
					MV1DrawModel(Soccerballx);
					DrawFormatString(300, 300, GetColor(255, 255, 255), "×４");
					break;
				}
				switch (g = 2)
				{
					MV1SetPosition(Soccerballx, VGet(290, 290, 0));
					MV1DrawModel(Soccerballx);
					DrawFormatString(300, 300, GetColor(255, 255, 255), "×３");
					break;
				}
				switch (g = 3)
				{
					MV1SetPosition(Soccerballx, VGet(290, 290, 0));
					MV1DrawModel(Soccerballx);
					DrawFormatString(300, 300, GetColor(255, 255, 255), "×２");
					break;
				}
				switch (g = 4)
				{
					MV1SetPosition(Soccerballx, VGet(290, 290, 0));
					MV1DrawModel(Soccerballx);
					DrawFormatString(300, 300, GetColor(255, 255, 255), "×１");
					break;
				}
				switch (g = 5)
				{
					MV1SetPosition(Soccerballx, VGet(290, 290, 0));
					MV1DrawModel(Soccerballx);
					DrawFormatString(300, 300, GetColor(255, 255, 255), "×0");
					break;

				}
				
			}
			

				// 指定位置にモデルを配置
				MV1SetPosition(Soccerball, VGet(x, y, z));
				MV1SetPosition(plane, VGet(0, 10, 0));
				MV1SetPosition(Soccerfield, VGet(1, 10.1, 1));
				MV1SetPosition(Soccergoal, VGet(-30, 0, 0));

				// ３Ｄモデルの描画
				MV1DrawModel(Soccerball);
				//MV1DrawModel(plane);
				MV1DrawModel(Soccerfield);
				MV1DrawModel(Soccergoal);

				DrawFormatString(240, 240, GetColor(255, 255, 255), "Escキーを押してください");

				DrawFormatString(50, 50, GetColor(255, 255, 255), "%3f.4,%3f.4,%3f.4", cx, cy, cz);

				SetCameraPositionAndTarget_UpVecY(VGet(cx, cy, cz), VGet(tx, 0.0f, 0.0f));

				ScreenFlip();
				Sleep(100);
			
		}

		//ここでボールをける前に加速度の初期化
		
		
		
		if (sleep > 120) {//二秒待ってから→fpsを定義する時間
			t += 1.0f / fps.mFps;
			
			if (x > -28) {	//ゴールについた時の条件
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
			if (y >= 1)	//地面よりも高い時の条件
				
				y = vy * t - 0.2f*G*t*t + 1.0f;
			
			else {

				if (vx <= 0) {
					vx = 0.998f*vx;
						
				}
			}
			if (x <= -20.4)
			{
				//ゴールポストの判定
				if (/*x >= -20.4 && y < 11 && z <= 10.4 && z >= 9.6 ||*/ x >= -20.4 &&x<=-20.3&& y < 11/* && z >= -10.4&&z <= -9.6 /*|| x >= -20.4 && y <11 && y>10 && -10.4 <= z <= 10.4*/)
				{
					x  -= vx * (1.0f / fps.mFps);;
					DrawFormatString(50, 50, GetColor(255, 255, 255), "反射");
				}

				addi++;
				if (y <= 10 && z >= -9.6 && 9.6 >= z) {
					DrawFormatString(50, 50, GetColor(255, 255, 255), "GOAL!!!!!!!!");
					//con = 'CON';
					if (addi == 1) {
						box = 'G';												//バイト型で送るもの
						buffer[0] = box;
					}

					if (addi > 300) {
						ini = false;
					}
					
				}

				else
				{
					DrawFormatString(50, 50, GetColor(255, 255, 255), "m9(^Д^)ﾌﾟｷﾞｬｰ");
					if (addi == 1) {
						box = 'O';												//バイト型で送るもの
						buffer[0] = box;
					}

					if (addi > 300) {
						ini = false;
					}
				}
				

				
			}
		}

		else {
			sleep++;//カウントして
		}

			DrawFormatString(0, 0, GetColor(255, 255, 255), "x=%.1f y=%.1f z=%.1f", x, y, z);
			DrawFormatString(0, 20, GetColor(255, 255, 255), "%.1f", fps.mFps);
		}
	DxLib_End();
	return 0;
}
