# pd_practice
## 金沢工業大学ロボティクス学科PD実践

### SPIKE-RT用のサンプルプログラム 

**使用方法(2025年10月）**
- コードのダウンロード  
- エクスプローラーのUbuntを開く  
- /user/programsに保存　
　追記：人によって保存場所が変わっている場合がある。Ubuntuの検索欄からprogramsで検索すると見つかる。  
  programsのディレクトリ直下に実行ファイルがあれば良い。  
  例：良い例   /user/programs/LCD_S1    
      駄目な例 /user/programsi〇〇/LCD_S1  
- cmd（コマンドプロンプト）を起動して、次のコマンドを打ち込む。  
  ./start.sh  

  下の表記が出れば成功！
  * 注意：Ubuntuを閉じてしまったら毎回このコマンドを実行するようこと *
  user@<自分のユーザーネーム>:~$ ./start.sh  
  * Starting Docker docker  
  user@98afe5f78c3b:~$
 
- ビルド：下記のコマンドを実行する。  
  ./build.sh <実行したいプログラム>  
  → arm-none-eabi-object...と表示されたらビルド完了

- Ubuntuを新たに開く  
- Spike hubをDFUモードにする（DFUモード：hubの電源を一度オフにしBluetoothボタンを押しながらhubに通信用コードを挿し、Bluetoothボタンが紫色に光った状態で5秒間押し色が変化するれば成功）  
./write.sh <実行したいプログラム>  
→ Finshedが表示されれば書き込み完了  
- 実行：Spike Hubの大きいボタンを押せば実行される。



