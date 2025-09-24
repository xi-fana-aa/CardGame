# 纸牌小程序

演示视频：https://www.bilibili.com/video/BV1XcthzcEzd

 1.  开发环境：cocos2dx 3.17
 2. 功能：
（1）手牌区替换
（2）桌面牌和手牌区顶部牌匹配
（3）回退功能
 3. 项目结构
 ```
Classes/
├── configs/      # 所有静态配置相关类
├── models/       # 运行时动态数据模型
├── views/        # 视图层，包含所有的UI展示组件
├── controllers/  # 控制器层，协调模型和视图
├── managers/     # 管理器层，提供全局性的服务和功能（作为controllers的成员；可持有model数据，禁止单例）
├── services/     # 服务层,提供无状态的服务，处理业务逻辑，不管理数据生命周期；（禁止持有model数据，可单例可静态方法）
└── utils/        # 工具类，提供通用功能
```

<!--stackedit_data:
eyJoaXN0b3J5IjpbMzkwMjExODA3XX0=
-->