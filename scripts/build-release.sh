
# build release sh

set -e

TAG="master"
WORKSPACE="./tmp-Ring"
TMP_DIR="./ring-linux64"
OUTPUT_TARGET="./ring-linux64.tar.gz"

RING_BIN="./bin/ring"
RING_STD="./std/"
RING_TEST_HELLO_WORLD="./test/helloworld.ring"


# apt-get update && \
# apt-get -y install git && \
# apt-get -y install make && \
# apt-get -y install flex && \
# apt-get -y install bison && \
# apt-get -y install g++

# git clone https://github.com/GeneralSandman/Ring $WORKSPACE
# cd $WORKSPACE #&& git checkout $TAG

make clean && make 

mkdir $TMP_DIR

cp    $RING_BIN              $TMP_DIR/ring
cp -r $RING_STD              $TMP_DIR/std
cp    $RING_TEST_HELLO_WORLD $TMP_DIR/helloworld.ring
echo  $TAG  >                $TMP_DIR/version.txt

tar -zcf $OUTPUT_TARGET $TMP_DIR