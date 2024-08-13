---
title: Qt 全局注册快捷键
tags: 
 - Qt
 - 快捷键
---





Qt 提供了 `QShortcut` 来实现快捷键的功能，不过它的响应范围只局限于窗口内。如果脱离了进程窗口，如在桌面，或者正在使用其他软件，是无法响应的。

要解决这样的问题可以使用 `Windows` 提供的 `API` 再结合qt的一些功能来实现一个全局可响应的快捷键。

直接行代码，首先在 `main` 函数添加快捷绑定进行注册

	MyGlobalShortCut *shortcut = new MyGlobalShortCut("Ctrl+Down", &w);
	QObject::connect(shortcut, SIGNAL(activated()), &w, SLOT(rec_testShotCutAns()));
然后添加 `MyGlobalShortCut.h`