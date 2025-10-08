# pd_practice
金沢工業大学ロボティクス学科PD実践のサンプルプログラム

SPIKE-RT用のサンプルプログラム 

使用方法(2024年11月）
コードのダウンロード
⇩
エクスプローラーのUbuntを開く
⇩
/user/programs　　に保存（追記　人によって保存場所が変わってします場合があります、ubuntuの検索欄からprogramsで検索すると出てきます）
programsのディレクトリ下直接実行ファイルがあればいいです
例：/user/programs/LCD_S1  
駄目な例/user/programsi〇〇/LCD_S1

cmdを起動
./start.sh

user@<自分のユーザーネーム>:~$ ./start.sh
 * Starting Docker docker
user@98afe5f78c3b:~$
この表記が出れば成功
注意：ubuntを閉じてしまったら毎回このコマンドを実行するように

./build.sh <実行したいプログラム>
→ arm-none-eabi-object...と表示されたらビルド完了

Ubuntuを開く

spike hubをDFUモードにする（DFUモード：hubの電源を一度オフにしBluetoothボタンを押しながらhubに通信用コードを指し、Bluetoothボタンが紫色に光った状態で5秒間押し色が変化するれば成功です）
./write.sh <実行したいプログラム>
→ Finshedが表示されれば書き込み完了

spike　hubの大きいボタンを押せば実行される


既存のテンプレートファイルをここの乗っているtemplateに更新すること
