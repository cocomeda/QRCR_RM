<!DOCTYPE html>
<head>
     <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width">
    <title>Code Reader for CoCo medaka2</title>

    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
    <script src="https://static.line-scdn.net/liff/edge/2.1/sdk.js"></script>

    <style>
        #popup {
            display: none;
            position: fixed;
            top: 50%;
            left: 50%;
            transform: translate(-50%, -50%);
            padding: 20px;
            background-color: #fff;
            border: 1px solid #ccc;
            box-shadow: 0 0 10px rgba(0,0,0,0.1);
            z-index: 1000;
        }
    </style>
</head>
<body>

<div id="popup">QR code scanned successfully!</div>

<script>
// LIFFの初期化
liff.init({ liffId: '1657196041-0B5JEMmG' }).then(() => {
    if (!liff.isLoggedIn()) {
        // ログインが必要な場合、ログインページを表示
        liff.login();
    } else {
        // ユーザーがログインしている場合、直ちにQRコードリーダーを開く
        openQRCodeReader1();
    }
}).catch((err) => {
    console.error('LIFFの初期化に失敗しました', err);
});

// QRコードリーダーを開く関数
function openQRCodeReader1() {
    liff.scanCode()
        .then(result => {
            if (result.value) {
                // QRコードのスキャンが成功した場合
                console.log("QRコードスキャン結果:", result.value);
                let qr_data = result.value; // QRコードのデータ

                sendQRDataToGAS1(qr_data); // Google Apps ScriptにQRコードデータを送信する
            } else {
                console.error('No QR code is detected');
            }
        })
        .catch(err => {
            console.error('Error scanning QR code:', err);
        })
        .finally(() => {
            // QRコードリーダーを閉じる
            //liff.closeWindow();
        });
}

// QRコードデータをGoogle Apps Scriptに送信する関数
function sendQRDataToGAS1(qr_data) {
    const idToken = liff.getIDToken();

    // QRコードデータとIDトークンをGASに送信
    $.ajax({
        url: 'https://script.google.com/macros/s/AKfycbx-3-4uwQbi-XJ87p8oY3uiQr9IE_R2lcfiEdH-2tkcN5UbcF7zCGS_ZwqqdT2CFuvO/exec',
        type: 'POST',
        data: { idToken: idToken, qr_data: qr_data },
        success: function (response) {
            // 成功時の処理
            console.log(response);
        },
        error: function (error) {
            // エラー時の処理
            console.error(error);
            alert('Failed to send QR data to GAS.');
        }
    });
}

// ポップアップを表示する関数
function showPopup() {
    const popup = document.getElementById('popup');
    popup.style.display = 'block';
    setTimeout(() => {
        popup.style.display = 'none';
    }, 3000); // 3秒後にポップアップを非表示にする
}
</script>
</body>
