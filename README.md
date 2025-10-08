# pd_practice
## 金沢工業大学ロボティクス学科PD実践

### SPIKE-RT用のサンプルプログラム 

**使用方法(2025年10月）**
- サンプルプログラムのダウンロード
PD実践で使用するサンプルプログラムを次の手順でダウンロードしましょう．

- 次のURLにアクセスして，下図赤丸の\[code\]をクリックし，赤丸で示している\[Download ZIP\]をクリックする。  
        https://github.com/demulab/pd_practice  

- エクスプローラーが開くので、パスに&yen;&yen;wsl$と入力し、その後、Ubuntu > home > user へ移動して、pd_practice-master.zipを保存する。  
<img width="1183" height="555" alt="SnapCrab_user - エクスプローラー_2025-10-8_16-7-44_No-00" src="https://github.com/user-attachments/assets/6b0f3d8e-fb33-4f82-a4c4-8b479d287adb" />

- ダウンロードしたpd_practice-master.zipにカーソール当ててマウスの右ボタンをクリックする。「これらのファイルを開くと、コンピュータに害を及ぼす可能性があります」と表示されるが、「OK」をクリックして、「すべて展開...」を選択して展開する。  
- 展開すると以下のフォルダができているので，sample_programの中の全ファイルを選択してコピーして、\home\user\programsにペーストする。
  - \home\user\pd_practice-master\pd_practice-master\sample_program  
  
- 下図のようなファイル構成になったら成功！  
<img width="1182" height="579" alt="SnapCrab_programs - エクスプローラー_2025-10-8_16-20-9_No-00" src="https://github.com/user-attachments/assets/53beb340-013d-4f66-9ffb-cd63e384c57c" />

- cmd（コマンドプロンプト）を起動して、次のコマンドを打ち込んでDockerを起動する。  
  ./start.sh  

  下の表記が出れば成功！  
  user@<自分のユーザーネーム>:\~$ ./start.sh  
  \* Starting Docker docker  
  user@98afe5f78c3b:\~$  
  **注意：Ubuntuを閉じてしまったら毎回このコマンドを実行してDockerを起動すること**
 
- ビルド：上で起動したDockerのターミナルで下記のコマンドを実行する。  
  ./build.sh <実行したいプログラム>
  - arm-none-eabi-object...と表示されたらビルド完了

- Ubuntuを新たに開く。Spikeにプログラムを書きこむときは、Dockerではなく、新しく開いたUbuntuのターミナルを使う。  
- Spike hubをDFUモードにする（DFUモード：hubの電源を一度オフにしBluetoothボタンを押しながらhubに通信用コードを挿し、Bluetoothボタンが紫色に光った状態で5秒間押し色が変化するれば成功）  
./write.sh <実行したいプログラム>
  - Finshedが表示されれば書き込み完了  
- 実行：Spike Hubの大きいボタンを押すとプログラムが実行される。



