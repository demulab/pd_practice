# pd_practice
## 金沢工業大学ロボティクス学科PD実践

### SPIKE-RT用のサンプルプログラム 

**使用方法(2025年10月）**
- コードのダウンロード  
-- このページの右上 <>Code → Download ZIPからダウンロードしてpd_practice-master.zipをDesktopに保存する。
- エクスプローラーを開き、パスに\\wsl$と入力し、その後、Ubuntu > home > user > programsと移動する。
<img width="1054" height="386" alt="SnapCrab_programs - エクスプローラー_2025-10-8_15-26-55_No-00" src="https://github.com/user-attachments/assets/5684a152-e2f0-461d-8e99-f8c083bf0ecf" />

- 保存したpd_practice-master.zipを/user/programsの中に保存する。　
- cmd（コマンドプロンプト）を起動して、次のコマンドを打ち込んでDockerを起動する。  
  ./start.sh  

  下の表記が出れば成功！  
  user@<自分のユーザーネーム>:~$ ./start.sh  
  \* Starting Docker docker  
  user@98afe5f78c3b:~$
  ** 注意：Ubuntuを閉じてしまったら毎回このコマンドを実行してDockerを起動すること**
 
- ビルド：下記のコマンドを実行する。  
  ./build.sh <実行したいプログラム>  
  → arm-none-eabi-object...と表示されたらビルド完了

- Ubuntuを新たに開く  
- Spike hubをDFUモードにする（DFUモード：hubの電源を一度オフにしBluetoothボタンを押しながらhubに通信用コードを挿し、Bluetoothボタンが紫色に光った状態で5秒間押し色が変化するれば成功）  
./write.sh <実行したいプログラム>  
→ Finshedが表示されれば書き込み完了  
- 実行：Spike Hubの大きいボタンを押せば実行される。



