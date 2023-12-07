

# start ubuntu docker

docker run -it -v /Users/bytedance/Desktop/Ring:/home/Ring --name test-ring-ubuntu ubuntu bash


apt-get update

apt-get -y install make && \
apt-get -y install flex && \
apt-get -y install bison && \
apt-get -y install g++ && \
apt-get -y install gdb

make clean && make


# start centos docker

docker run -it -v /Users/bytedance/Desktop/Ring:/home/Ring --name test-ring-centos centos bash


cd /etc/yum.repos.d/

sed -i 's/mirrorlist/#mirrorlist/g' /etc/yum.repos.d/CentOS-*
sed -i 's|#baseurl=http://mirror.centos.org|baseurl=http://vault.centos.org|g' /etc/yum.repos.d/CentOS-*
yum update -y



yum install make

yum install epel-release

yum debuginfo-install libgcc-8.5.0-4.el8_5.x86_64 libstdc++-8.5.0-4.el8_5.x86_64

yum install clang

yum install flex

yum install bison