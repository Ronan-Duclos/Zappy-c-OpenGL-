# gunzip -c libpng-1.6.12.tar.gz | tar -xopf -
# tar -zxvf libpng-1.6.12.tar.gz
# tar -zxvf zlib-1.2.8.tar.gz
 cd libpng-1.6.12
 ./configure --prefix="/nfs/zfs-student-4/users/2013/tmielcza/Sujets/UNIX II/Zappy/ZGFX"
# cp scripts/makefile.darwin makefile
make
make install
make clean