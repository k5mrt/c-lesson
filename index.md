---
title: "トップページ"
layout: page
---

karino2の暇つぶしプログラム教室のC言語編のページです。

C言語の入門書くらいは読んだがそこから先が良くわからん、という人向けに、
暇つぶし程度に教える、という事をやるサイトです。

# あらすじ

twitterでプログラム教えてもいいって言ったら教えてほしいという人がいたので教える事にする。
少し話を聞いたところ、

1. まずはC言語でちゃんとプログラム書く事を教えてほしい
2. C言語の本などは読んでいて、ArduinoやRasbherryPiなどの経験はちょっとある
3. 大学院生だがCS系の専攻では無い

という感じらしい。

### 進め方

適当に課題をやってもらいつつ[gitter](https://gitter.im/karino2_program_lesson/c-lesson)で質問に答えたり添削したりして、
たまに補足したり説明した方がいいと思う事は本を紹介したり説明をしたり動画を作ったりします。

とりあえず始める人はgitterで自己紹介くらい簡単にしてくれると嬉しいです。

課題は https://github.com/karino2/c-lesson.git をフォークして、このサイトの指示に従ってやってもらいます。

基本的には相手の反応見てから進め方を考えます。


## C言語でやる事、やるべきでない事

2018年現在、C言語を学ぶ意義というとどういうあたりだろう？

1. Arduinoやbaremetalに近い環境で、小さなランタイムで動く
2. バイナリ処理
3. 数千行くらいのちょっと大きいコード

とういあたりと思った。
逆にやるべきでない事は

1. ライブラリなどをたくさん使う
2. 大規模な開発

という感じかな、と思った。
ライブラリ使う系はgolangなどの方がいいし、大規模な開発はC++なりRustなりの方が良さそう。

現在では、C言語の良さは小さいバイナリで生きると思う。

というような事を動画にしてみた。

<iframe width="560" height="315" src="https://www.youtube.com/embed/0yFS4UHgmHU" frameborder="0" allow="autoplay; encrypted-media" allowfullscreen></iframe>

以上を踏まえて、教える事も考えたい


### 教えようと持っている事

1. 入門書で学んだ事をちゃんと消化するために実際のコードを書いてみる
2. ある程度の規模のコードを書くためのファイルの分割やインターフェースを考える事などを実際にやる
3. ランタイムが無い環境で良く使うコレクションなどを自力で書く
4. objdumpやobjcopy、アセンブリ言語なども多少はやる（ただし仮想メモリとかを本気でやりはしない）

こんな感じでどうかな、と思っている。

実際に入門書読んだだけでポインタでも関数ポインタでも完璧、という事は無いと思うので、
C言語自体の説明は折に触れてやっていきたい。


# 事前準備

- 簡単なgitの使い方
    - [https://git-scm.com/book/ja/v2/](https://git-scm.com/book/ja/v2/)の3章くらいまでやっておく
- なんかC言語の入門書くらい
  - [菊田さんのレポート](https://yoheikikuta.github.io/clesson_first_postscript/)によると、C言語の入門書に加えて「ふつうのLinuxプログラミング」の写経くらいやっておくと十分そう。

[amazon: ふつうのLinuxプログラミング 第2版　Linuxの仕組みから学べるgccプログラミングの王道](https://amzn.to/43gOdCE)


# 第一回 簡易PostScriptインタプリタを作ろう

やる事

- ハッシュ、線形リスト、スタックの実装
- 簡単なインタープリタの実装
   - 言語はPost Scriptのサブセット
   - 実行可能配列（関数リテラル相当）、ifelse、repeatくらいまで
   - VM化とバイトコードへのコンパイルもやる
- 3000行くらい。(テスト抜いて1500行くらい）


[第一回 簡易PostScriptインタプリタを作ろう](forth_modoki.md)

# 第二回 簡易アセンブラとディスアセンブラを作ろう

やる事

- QEMUでARMの簡単なバイナリを動かす
- ARMの簡単なアセンブラ、ディスアセンブラを作る
- 二分木やステートマシンなど、第一回の内容の補完的な内容もやっておく

[第二回 簡易アセンブラとディスアセンブラを作ろう](arm_asm.md)

おまけ [bare metalでのgdb入門](gdb.md)

# 第三回 バイナリやアセンブリから見るC言語とリンカ

やる事

- objdumpなどの知識を手掛かりに、オブジェクトファイルやシンボルの解決を学ぶ
- elfやリンカ、ローダーなどの基本を学ぶ
- text, data, bssとC言語の関係を学ぶ
- コンパイラの吐くアセンブリのソースを調べて、C言語をアセンブリから理解する
- 最後におまけとして第一回で作ったインタープリタの簡易版のJITを作る

第三回は第二回の続きになります。第二回を終えてから読む事を推奨します。

[第三回 バイナリやアセンブリから見るC言語とリンカ](casm_link_load.md)


# やった人の感想

菊田さん
- [c-lesson 第一回「簡易PostScriptインタプリタを作ろう」を終えた](https://yoheikikuta.github.io/clesson_first_postscript/)
- [c-lesson 第二回「簡易アセンブラとディスアセンブラを作ろう」を終えた](https://yoheikikuta.github.io/clesson_second_asm/)
- [c-lesson 第三回「バイナリやアセンブリから見るC言語とリンカ」を終えて全内容を終了した](https://yoheikikuta.github.io/clesson_casm_link/)

t-sinさん
- [C言語の勉強: 簡易PostScriptインタプリタ編 - 技術の記録 - Ibotenic](https://t-sin.github.io/techblog/2021-07-21-c-lesson-01.html)
- [C言語の勉強: 簡易逆アセンブラ・アセンブラ編 - 技術の記録 - Ibotenic](https://t-sin.github.io/techblog/2021-09-10-c-lesson-02.html)
- [C言語の勉強: バイナリ・アセンブリを通してみるC言語編 (それとJITコンパイル) - 技術の記録 - Ibotenic](https://t-sin.github.io/techblog/2022-02-22_c-lesson-03.html)