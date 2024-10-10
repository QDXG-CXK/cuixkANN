# cuixkANN
clone仓库时要递归的clone包含的子仓库，例如src/路径下的faiss库
```shell
git clone --recurse-submodules  https://github.com/QDXG-CXK/cuixkANN.git
```
然后进入项目目录执行编译操作
```shell
sed -i 's/\r//g' build.sh
./build.sh
```
