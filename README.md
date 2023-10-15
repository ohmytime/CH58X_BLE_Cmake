# CH58X-BLE_CMake
基于沁恒的BLE/BLE_UART

## ⑴ 编译

摆脱eclipse编译环境，使用vscode编辑代码。

此仓库为cmake模板，请根据自己的工程进行适当修改。

请在CmakeLists.txt文件内更改`TOOLPATH`的变量为你的工具链路径。

使用脚本编译：

```shell
sh build.sh
```

如果是手动编译，可选择如下两个方法


```shell
A和B方法任选其一即可

A、使用cmake生成eclipse Makefile工程
cmake -G"Eclipse CDT4 - Unix Makefiles" ..
如果没有把make.exe加入系统path:
cmake -G"Eclipse CDT4 - Unix Makefiles" -D"你的路径/make.exe"  ..

B、使用cmake生成ninja工程
cmake -G"Ninja" ..
如果没有把ninja.exe加入系统path:
cmake -G"Ninja" -D"你的路径/ninja.exe" ..
```

## ⑵ 调试
Mac OS M芯片平台：

### Tips :
- WCH-Link :需要设置好正确的模式

    （[说明书中文版](https://www.wch.cn/downloads/WCH-LinkUserManual_PDF.html))([LinkUserManual](https://www.wch-ic.com/downloads/WCH-LinkUserManual_PDF.html))

    如果是ARM架构的芯片，则设置为ARM模式，否则需要设置为RISC-V模式

- 安装好 libusb驱动

    在MBA下，需要安装Apple版 + Intel版的 libusb驱动（因为沁恒的OpenOCD依赖的是Intel的libusb）

- 把WCH-Link 连接好芯片，然后芯片开启两线仿真，并且把开发板连接到电脑

- 安装cortex-debug 1.4.4版本

    因为沁恒使用的是GCC8，cortex-debug 1.4.4版本是最后兼容GCC8的版本了。(再次敦促：沁恒，该更新Toolchain了 ！！)


最后就可以Debug了

---

## ⑶ MRS Linux Mac Toolchain & OpenOCD 下载说明
### FLASH CMD


[RISC-V]

erase all
```
sudo ./openocd -f wch-riscv.cfg -c init -c halt -c "flash erase_sector wch_riscv 0 last " -c exit
```
program
```
sudo ./openocd -f wch-riscv.cfg  -c init -c halt  -c "program xxx.hex/bin/elf" -c exit
```

verify
```
sudo ./openocd -f wch-riscv.cfg -c init -c halt -c "verify_image xxx.hex/bin/elf" -c exit
```

reset and resume
```
sudo ./openocd -f wch-riscv.cfg -c init -c halt -c wlink_reset_resume -c exit
```


[ARM]

erase all
```
sudo ./openocd -f wch-riscv.cfg -c init -c halt -c "flash erase_sector wch_riscv 0 last " -c exit
```
program
```
sudo ./openocd -f wch-arm.cfg  -c init -c halt  -c "program xxx.hex/bin/elf " -c exit
```

verify
```
sudo ./openocd -f wch-arm.cfg -c init -c halt -c "verify_image xxx.hex/bin/elf" -c exit
```


！备注：如果因为权限无法运行，执行
```
chmod 755 ./openocd
```

参考链接：

https://www.cnblogs.com/milton/p/17368566.html

https://www.wch.cn/bbs/thread-88583-1.html

https://www.cnblogs.com/wahahahehehe/p/16896184.html

https://bbs.21ic.com/icview-3291850-1-1.html

https://jia.je/hardware/2022/04/19/wch-ch32v307-eval/

