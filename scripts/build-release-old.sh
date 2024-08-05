
# build release sh


git clone https://GeneralSandman/Ring Ring && cd Ring

git checkout -

#  -------------------------------------------


# start ubuntu docker
docker run --cap-add=SYS_PTRACE --security-opt seccomp=unconfined \
    -it -v /Users/lizhenhu/Desktop/Ring:/home/Ring --name test-ring-ubuntu ubuntu bash

# install ubuntu build dependicy
apt-get update && \
apt-get -y install make && \
apt-get -y install flex && \
apt-get -y install bison && \
apt-get -y install g++ && \
apt-get -y install gdb && \
apt-get -y install valgrind

# build
cd /home/Ring && \
make cleandeps && make clean && make && make install && make testall && make testdump



#  -------------------------------------------

# start centos docker
docker run -it -v /Users/lizhenhu/Desktop/Ring:/home/Ring --name test-ring-centos centos bash

# install centos build dependicy
cd /etc/yum.repos.d/ && \
sed -i 's/mirrorlist/#mirrorlist/g' /etc/yum.repos.d/CentOS-* && \
sed -i 's|#baseurl=http://mirror.centos.org|baseurl=http://vault.centos.org|g' /etc/yum.repos.d/CentOS-* && \
yum update -y && \
    yum install -y make && \
    yum install -y flex && \
    yum install -y clang && \
    yum install -y gdb && \
    yum install -y wget

# install bision 3.8.2
cd /home && \
    wget https://ftp.gnu.org/gnu/bison/bison-3.8.2.tar.gz && \ 
    tar -zxvf bison-3.8.2.tar.gz && \
    cd bison-3.8.2 && \
    ./configure && \
    make && \
    make install && \
    /usr/local/bin/bison --version

    
    
# build
cd /home/Ring && \
make cleandeps && make clean && make && make install && make testall && make testdump





# ---------------------------

valgrind --leak-check=full \
    --show-leak-kinds=all  \
    --track-origins=yes -s \
    ./bin/ring run ./test/024-array-class/for-access-002.ring 2>valgrind.result


