
# build release sh


git clone https://GeneralSandman/Ring Ring && cd Ring

git checkout -




# start ubuntu docker

docker run --cap-add=SYS_PTRACE --security-opt seccomp=unconfined \
    -it -v /Users/bytedance/Desktop/Ring:/home/Ring --name test-ring-ubuntu ubuntu bash


apt-get update && \
apt-get -y install make && \
apt-get -y install flex && \
apt-get -y install bison && \
apt-get -y install g++ && \
apt-get -y install gdb && \
apt-get -y install valgrind && \
cd /home/Ring && \
make clean && make && make install && make testall


valgrind --leak-check=full \
    --show-leak-kinds=all  \
    --track-origins=yes -s \
    ./bin/ring run ./test/024-array-class/for-access-002.ring 2>valgrind.result



# start centos docker

docker run -it -v /Users/bytedance/Desktop/Ring:/home/Ring --name test-ring-centos centos bash


cd /etc/yum.repos.d/ && \
sed -i 's/mirrorlist/#mirrorlist/g' /etc/yum.repos.d/CentOS-* && \
sed -i 's|#baseurl=http://mirror.centos.org|baseurl=http://vault.centos.org|g' /etc/yum.repos.d/CentOS-* && \
yum update -y && \
    yum install make && \
    yum install flex && \
    yum install bison && \
    yum install clang && \
    yum install gdb
    
cd /home/Ring && \
make clean && make && make install && make testall

