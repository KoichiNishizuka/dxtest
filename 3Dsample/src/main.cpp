#include <DxLib.h>

int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int){
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen( DX_SCREEN_BACK );

	//3Dモデルの読み込み
	int ModelHandle = MV1LoadModel( "dat/Lat式ミク/Lat式ミクVer2.3_Normal.pmd" ) ;

	//奥行0.1～1000までをカメラの描画範囲とする
	SetCameraNearFar( 0.1f, 1000.0f ) ;

	//(0,10,-20)の視点から(0,10,0)のターゲットを見る角度にカメラを設置
	SetCameraPositionAndTarget_UpVecY( VGet( 0, 10, -20 ), VGet( 0.0f, 10.0f, 0.0f ) ) ;

	while(!ScreenFlip()&&!ProcessMessage()&&!ClearDrawScreen()){

		// ３Ｄモデルの描画
		MV1DrawModel( ModelHandle ) ;

	}

	DxLib_End();
	return 0;
} 