//
// Created by 86188 on 2023/8/27.
//
#include <iostream>

using namespace std;

/*
 * 适配器模式：让不兼容的接口可以在一起工作
 *
 * 电脑 => 投影 => 投影仪上 VGA HDMI TypeC
 *
 * VGA 接口的电脑：投影仪也是 VGA 接口
 * */

// 抽象类
class VGA {
public:
    virtual void play() = 0;
};

// 投影仪类
class TV01 : public VGA {
public:
    void play() {
        cout << "Play from VGA" << endl;
    }
};

// 只支持 VGA 接口
class Computer {
public:
    // 由于电脑只支持 VGA 接口，所以该方法的参数只能支持 VGA 接口的指针/引用
    void playVideo(VGA *pVGA) {
        pVGA->play();
    }
};

// 进了一批新的投影仪，但是新的投影仪只支持HDMI 接口
// #1 新接口的基类
class HDMI {
public:
    virtual void play() = 0;
};

// 投影仪类
// #2 新接口的功能类
class TV02 : public HDMI {
public:
    void play() {
        cout << "Play from HDMI" << endl;
    }
};

/*
 * 方法 1：换一个支持 HDMI接口的电脑，这就叫代码重构
 * 方法 2：买一个转换头 将 VGA 转化为 HDMI 信号，叫添加适配器类
 * */

// #3 添加适配器类
class VGAToHDMIAdapter : public VGA { // 一定要继承老接口
public:
    VGAToHDMIAdapter(HDMI *p) : pHdmi(p) {}

    void play() {  // 该方法相当于转换头
        pHdmi->play();
    }

private:
    HDMI *pHdmi;
};

int main() {
    Computer computer;
    computer.playVideo(new TV01()); // 通过电脑连接 TV01 播放
//    computer.playVideo(new TV02()); // 无法使用 TV02 投影仪
    // #4 使用适配器类
    computer.playVideo(new VGAToHDMIAdapter(new TV02())); // 使用适配器
    return 0;
}