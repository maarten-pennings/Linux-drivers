# 2 Params
Inspiration from [embetronicx](https://embetronicx.com/tutorials/linux/device-drivers/linux-device-driver-tutorial-part-3-passing-arguments-to-device-driver/).

## Building
 - get kernel headers `sudo apt-get install raspberrypi-kernel-headers` if not done previously
 - make with `sudo make`

## Startup
We can initialize kernel module parameters during `insmod`.

```
sudo insmod params.ko param_charp="startup"
```

We can use the files created in `/sys/modules` to read or write the parameters.

```
$ cd /sys/module/params/parameters/
$ ls -al
total 0
drwxr-xr-x 2 root root    0 Dec 22 17:09 .
drwxr-xr-x 6 root root    0 Dec 22 17:09 ..
-rw------- 1 root root 4096 Dec 22 17:09 param_bools
-rw------- 1 root root 4096 Dec 22 17:09 param_charp
-rw-rw---- 1 root root 4096 Dec 22 17:09 param_int
```

Note that only `params_int` has `rw` for group (as coded in the source) and that 
`params_short` does not even appear (it has access flags 0 in the code).

## Test int

```
$ sudo cat param_int
7
$ echo "12" | sudo tee param_int
12
$ sudo cat param_int
12
```

Note `sudo echo "12" > param_int` does not work, because teh scope of `sudo` stops at `>`.

The module is aware of types, an refuses text for an int.

```
$ echo text | sudo tee param_int
text
tee: param_int: Invalid argument
```

## Test charp

```
$ sudo cat param_charp
startup
$ echo "hi there" | sudo tee param_charp
hi there
$ sudo cat param_charp
hi there

```

You might want to try `echo -n "hi there"` to get rid of the newline.


## Test bools

At first the bools array is empty (count is 0). 
Then we try to write too much, that fails ("Invalid argument").
Finally we write three booleans. 
They are also visible on `rmmod`.

```
$ sudo cat param_bools
$ echo "N,Y,N,Y,Y,N" | sudo tee param_bools
N,Y,N,Y,Y,N
tee: param_bools: Invalid argument
$ echo "N,Y,Y" | sudo tee param_bools
N,Y,Y
$ sudo cat param_bools
N,Y,Y
```

We can also use 0 and 1 for bools, but not T and Finally

```
$ echo "0,1,0" | sudo tee param_bools
0,1,0
$ echo "T,F" | sudo tee param_bools
T,F
tee: param_bools: Invalid argument
$ echo "True,False" | sudo tee param_bools
True,False
tee: param_bools: Invalid argument
$ echo "true,false" | sudo tee param_bools
true,false
tee: param_bools: Invalid argument
```

Upon exit, we see all values

```
$ sudo rmmod params
$ dmesg
[74955.463865] params: inserted successfully...
[75090.792139] params: param_int = 12
[75090.792157] params: param_short = 0
[75090.792166] params: param_charp = "hi there
               "
[75090.792176] params: param_bools_count = 3
[75090.792185] params: param_bool[0]=0
[75090.792194] params: param_bool[1]=1
[75090.792202] params: param_bool[2]=0
[75090.792211] params: removed successfully...
```

(end)

