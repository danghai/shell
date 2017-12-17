#!/bin/sh
echo "Hello World"
read USER_NAME
echo "Hello $USER_NAME"
echo "Create the $USER_NAME"
touch $USER_NAME
