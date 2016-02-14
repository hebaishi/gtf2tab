#!/bin/sh
BINS="gtf2tab"

LINUX_COMMAND="tar cvzf"
LINUX_OUTPUT="gtf2tab_x86_64.tar.gz"

cd bin
if [ "$TRAVIS_OS_NAME" = "linux" ]
then
  $LINUX_COMMAND $LINUX_OUTPUT $BINS
fi
