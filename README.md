# C++ Argument Parser

C++で実装した自作のコマンドライン引数パーサーである。
コマンドライン引数の解析、型変換、デフォルト値、オプション引数、フラグ引数を行う。

現在、以下の機能に対応している。

- 位置引数
- オプション引数
    - --port / -p (短縮名)
- オプション引数のデフォルト値
- フラグ引数
    - --verbose / -v (短縮名)
- 引数の説明（help）
    - --help / -h
- 型付きの値の取得
- 現在対応している型
    - int, int64, float, double, char, std::string, bool


## 必要な環境
- C++17以降
- CMake

## ビルド
ビルドは`build.sh`を用いて実行できる。
```bash
./build.sh
```
デフォルトでは、g++のコンパイラは、パスを検索して使用する。
C++コンパイラのパスを指定する場合は、`--compiler`あるいは`-c`オプションを付けて実行する。
```bash
./build.sh --compiler <C++ compiler path>
```
または、
```bash
./build.sh -c <C++ compiler path>
```
ビルドが完了すると、build/ディレクトリに静的ライブラリが生成される。
```text
build/libargument_parser.a
```


## ArgumentParser使用
`argument_parser/argument_parser.hpp`をインクルードし、`ArgumentParser`クラスの変数を作成することで引数解析を
行うことができる。

```cpp
#include <argument_parser/argument_parser.hpp>

int main(const int argc, const char* argv[]) {
    ArgumentParser parser("parser test");
    // ...
}
```

`ArgumentParser`のコンストラクタにはプログラム名を指定できる。
```cpp
ArgumentParser parser("parser test");
```
この場合、ヘルプ表示時に、以下のようにプログラム名が表示される。
```text
Program: parser test
```

プログラム名を指定する必要がない場合は、省略できる。
```cpp
ArgumentParser parser;
```

## 引数の種類
ArgumentParserでは、以下の3種類の引数を使用できる。
- 位置引数
- オプション引数
- フラグ引数

### 位置引数
位置引数は`AddPositionalArgument`関数を使用して定義する。
`AddPositionalArgument`関数には、以下の引数を指定する。

|引数|説明|
|---|---|
|name|引数の説明|
|type|引数の型|
|help|引数の説明|

例えば、以下のように位置引数を定義する。
```cpp
parser.AddPositionalArgument(
    "input",          // name
    ArgType::STRING,  // type
    "input file"      // help
);

parser.AddPositionalArgument(
    "output",         // name
    ArgType::STRING,  // type
    "output file"     // help
);
```

位置引数を定義した場合、実行時に以下のようにして引数を指定する。
```bash
./a.out input.dat output.dat
```
位置引数の順番は、ファイル内で定義された順番に対応する。
```text
input.dat  -> input
output.dat -> output
```
位置引数は必須引数として扱われるため、定義した位置引数は実行時に必ず指定する必要がある。


### オプション引数

オプション引数は`AddOptionalArgument`関数を用いて定義する。
`AddOptionalArgument`関数の引数には、引数の名前(name)、引数の型(type)、引数の説明(help)、
引数のでデフォルト値(default_value)を渡すことができる。
```cpp
// 引数にname、type、helpのみ渡す場合
parser.AddOptionalArgument(
    "port",               // name
    ArgType::INT,         // type
    "Server port number"  // help
);

// default_valueも渡す場合
parser.AddOptionalArgument(
    "port",               // name
    ArgType::INT,         // type
    8080,                 // default_value
    "Server port number"  // help
);
```

引数の名前には、短縮した引数の名前(short_name)も指定できる。
```cpp
parser.AddOptionalArgument(
    "port",               // name
    'p',                  // short_name
    ArgType::INT,         // type
    8080,                 // default_value
    "Server port number"  // help
);
```
位置引数を定義した場合、実行時に以下のように`--`を付けてコマンドライン引数を与える。
```bash
./a.out --port 8888
```
短縮した引数の名前を指定した場合は、`-`を付けて引数を与えうことができる
```bash
./a.out -p 8888
```
オプション引数は、必ずしも実行時に引数を渡す必要はない。以下のように`--port`を指定せずに実行した場合、引数の定義のときに指定したデフォルトの値が使用される。ただし、定義のときにデフォルトの値を指定していない場合、値が`null`になるので注意する。
```
./a.out --name user
```


### フラグ引数
フラグ引数は、`AddFlag`関数を用いて定義する。
`AddFlag`関数の引数には、引数の名前(name)、短縮した引数名(short_name)、引数の説明(help)を渡すことができる。
```cpp
parser.AddFlag(
    "verbose",
    "Test verbose"
);

// short_nameも渡す場合
parser.AddFlag(
    "verbose",
    'v',
    "Test verbose"
);
```
定義されたフラグ引数のデフォルト値は`false`である。
プラグラムの実行時に、以下のように`--`あるいは`-`を付けてフラグ引数を指定した場合、フラグ引数の値は
`true`となる。
```bash
./a.out --verbose

# 短縮した引数名の場合 
./a.out -v
```

## 値の取得
定義した引数の値は`Get<T>`関数を使用して取得する。
`T`には、取得したい型を指定する。
オプション引数やフラグ引数では短縮した引数名を指定できるが、値の取得では短縮した引数名は指定できないことに注意する。
```cpp
const std::string input = parser.Get<std::string>("input");

const auto output = parser.Get<std::string>("output");

const int port = parser.Get<int>("port");

const auto name = parser.Get<std::string>("name");

const bool verbose = parser.Get<bool>("verbose");
```

## examples
`examples/main.cpp` は `ArgumentParser` の使用例である。

```cpp
#include <argument_parser/argument_parser.hpp>
#include <iostream>


int main(const int argc, const char* argv[]) {
    ArgumentParser parser("parser test");

    parser.AddPositionalArgument("input", ArgType::STRING, "input file");
    parser.AddPositionalArgument("output", ArgType::STRING, "output file");
    parser.AddOptionalArgument("port", 'p', ArgType::INT, 8080, "Server port number");
    parser.AddOptionalArgument("name", ArgType::STRING, "User name");
    parser.AddFlag("verbose", 'v', "Test verbose");
    parser.Parse(argc, argv);

    std::cout << parser.Get<std::string>("input") << std::endl;
    std::cout << parser.Get<std::string>("output") << std::endl;
    std::cout << parser.Get<int>("port") << std::endl;
    std::cout << parser.Get<std::string>("name") << std::endl;
    std::cout << parser.Get<bool>("verbose") << std::endl;

    return 0;
}
```

`ArgumentParser`ライブラリをビルドした後、examplesディレクトリから以下のようにコンパイルできる。
```bash
cd examples

g++ -std=c++17 main.cpp \
    -I../include \
    -L../build \
    -largument_parser\
    -o parser_test
```
コンパイル後、以下のように引数を指定して実行する。
```bash
./parser_test input.dat output.dat --port 8888 --name user --verbose
```
この場合、各引数の値は以下の通りになる。
```text
input   = "input.dat"
output  = "output.dat"
port    = 8888
name    = "user"
verbose = true
```
したがって、プログラムの出力は、
```text
input.dat
output.dat
8888
user
1
```
となる。

短縮した引数名を使用して実行する場合は、以下のようになる（結果は同じ）。
```bash
./parser_test input.dat output.dat -p 8888 --name user -v
```

## ヘルプ
実行時、`--help`または`-h`を指定すると、引数の説明を表示できる。
上記の`examples/main.cpp`の場合は、以下を実行する。
```bash
./parser_test --help
# または
./parser_test -h
```

以下のような引数の説明が表示される。
```text
Program: parser test
Arguments:
 input
     input file
 output
     output file
 --name
     User name
 --port [default: 8080]
     Server port number
 --verbose [default: false]
     Test verbose
```
