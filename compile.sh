cd src
make clean install
mv project ../
cd ..
strip --strip-all project
