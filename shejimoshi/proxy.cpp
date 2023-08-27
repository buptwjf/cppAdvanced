//
// Created by 86188 on 2023/8/27.
//
#include <iostream>
#include <memory>

using namespace std;

/*
 * 代理模式 Proxy
 * 通过代理累来控制实际对象的访问权限
 * 客户   助理Proxy     老板 委托类
 **/

// 基类：抽象类
class VideoSit {
public:
    virtual void freeMovie() = 0;   // 免费
    virtual void vipMovie() = 0;    // vip
    virtual void ticketMovie() = 0; // 用券
};

// #1 委托类，拥有所有的功能
class FixBugVideoSite : public VideoSit {
public:

    void freeMovie() {
        cout << "free movie " << endl;
    }

    void vipMovie() {
        cout << "vip Movie" << endl;
    }

    void ticketMovie() {
        cout << "ticket Movie" << endl;
    }
};

// #2 代理类
class FreeVideoSiteProxy : public VideoSit {
public:
    FreeVideoSiteProxy() { pVideo = new FixBugVideoSite(); } // #3 代理类继承委托类

    ~FreeVideoSiteProxy() { delete pVideo; }

    void freeMovie() {
        pVideo->freeMovie(); //通过代理类，访问委托的对象
    }

    void vipMovie() {
        cout << "You can' t see vip Movie, you are free member." << endl;
    }

    void ticketMovie() {
        cout << "You need tickets" << endl;
    }

private:
    VideoSit *pVideo;
};

// #2 代理类
class VipVideoSiteProxy : public VideoSit {
public:
    VipVideoSiteProxy() { pVideo = new FixBugVideoSite(); }

    ~VipVideoSiteProxy() { delete pVideo; }

    void freeMovie() {
        pVideo->freeMovie(); //通过代理类，访问委托的对象
    }

    void vipMovie() {
        cout << "You can' t see vip Movie，you are free member." << endl;
    }

    void ticketMovie() {
        pVideo->ticketMovie();
    }

private:
    VideoSit *pVideo;
};


// #2 代理类
class TicketVideoSiteProxy : public VideoSit {
public:
    TicketVideoSiteProxy() { pVideo = new FixBugVideoSite(); }

    ~TicketVideoSiteProxy() { delete pVideo; }

    void freeMovie() {
        pVideo->freeMovie(); //通过代理类，访问委托的对象
    }

    void vipMovie() {
        pVideo->vipMovie();
    }

    void ticketMovie() {
        pVideo->ticketMovie();
    }

private:
    VideoSit *pVideo;
};

void show(unique_ptr<VideoSit> &p) { // 由于 unique_ptr 没有拷贝赋值，因此只能传引用
    p->freeMovie();
    p->vipMovie();
    p->ticketMovie();
}

int main() {
    unique_ptr<VideoSit> p1(new FixBugVideoSite());
    /* 直接使用委托类，无法针对不同的用户设定不同的权限 */
    show(p1);

    unique_ptr<VideoSit> p2(new FreeVideoSiteProxy());
    show(p2);
    unique_ptr<VideoSit> p3(new VipVideoSiteProxy());
    show(p3);
    unique_ptr<VideoSit> p4(new TicketVideoSiteProxy());
    show(p4);
    return 0;

}