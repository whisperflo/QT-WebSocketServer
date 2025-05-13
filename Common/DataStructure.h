typedef enum
    {
        PCSDATA,             // 24台pcs的概览信息排列
        BMSBASICINFORMATION, // 单台bms的基本信息
        PCSSTATUS,           // PCS各个状态的运行数量、输出总有功功率、输出总无功功率等
        BMSSTATUS,
        SYSTEMINFORMATION, // 系统总览包含系统状态SOC 日充日放、总充总放等信息
        PCSEVERYDATA,      // 单台PCS的实时数据
        BMSEVERYDATA,      // 单台BMS12簇的概览信息
        ENERYFLOWDATA,     // 能量流动图
        UNKNOWNPATH

    } PathType;
