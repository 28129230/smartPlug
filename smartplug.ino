int TVPlugState=0;
int StereoAMPPlugState = 0;
int AvAMPPlugState=0;
int CTSTPlugState=0;
int NetPlugState=0;
int NetSTPlugState=0;
int DiskPlayPlugState=0;
int otherPlugState=0;
int playMusicState=0;
int watchTVState=0;
int watchAVstate=0;
String contComm="";
/*---------------以上初始化所有的控制命令的状态都是关闭-----------------------*/
int plugControl;//读取串口发送来的指令
int plugs[8] = {2,3,4,5,6,7,8,9};//分配控制插座的开关引脚
void setup()
{
	for(int i=0;i<8;i++)//初始化数字引脚2-9为高电平，控制8个继电器状态为关闭
	{
		pinMode(plugs[i],OUTPUT);
		digitalWrite(plugs[i],HIGH);
	}
	Serial.begin(115200);//打开串口通讯
}

void TVPlug(int state)//电视机插口开关函数
{
	if (state == 1)// 状态置为1表示插口通电
	{
		digitalWrite(plugs[0],LOW);//使用数字引脚2为低电平控制继电器引脚1，开关通电
		TVPlugState=1;//将电视插口状态置为1，表示通电状态
	}
	else//状态置为0表示插口断电
	{
		digitalWrite(plugs[0],HIGH);//使用数字引脚2为高电平控制继电器引脚1，开关关闭
		TVPlugState=0;//将电视插口状态置为0，表示断电状态
	}
}

void StereoAMPPlug(int state)//立体声功放（包括前级、后级）插口开关函数
{
	if (state == 1)// 状态置为1表示插口通电
	{
		digitalWrite(plugs[1],LOW);//使用数字引脚3为低电平控制继电器引脚2，开关通电
		StereoAMPPlugState=1;//将插口状态置为1，表示通电状态
	}
	else//状态置为0表示插口断电
	{
		digitalWrite(plugs[1],HIGH);//使用数字引脚3为高电平控制继电器引脚2，开关关闭
		StereoAMPPlugState=0;//将插口状态置为0，表示断电状态
	}
}

void AvAMPPlug(int state)//AV功放（包括前级、后级）插口开关函数
{
	if (state == 1)// 状态置为1表示插口通电
	{
		digitalWrite(plugs[2],LOW);//使用数字引脚3为低电平控制继电器引脚3，开关通电
		AvAMPPlugState=1;//将插口状态置为1，表示通电状态
	}
	else//状态置为0表示插口断电
	{
		digitalWrite(plugs[2],HIGH);//使用数字引脚3为高电平控制继电器引脚3，开关关闭
		AvAMPPlugState=0;//将插口状态置为0，表示断电状态
	}
}

void CTSTPlug(int state)//有线电视机顶盒（Cable TV set top）插口开关函数
{
	if (state == 1)// 状态置为1表示插口通电
	{
		digitalWrite(plugs[3],LOW);//使用数字引脚5为低电平控制继电器引脚4，开关通电
		CTSTPlugState=1;//将有线电视机顶盒插口状态置为1，表示通电状态
	}
	else//状态置为0表示插口断电
	{
		digitalWrite(plugs[3],HIGH);//使用数字引脚5为高电平控制继电器引脚4，开关关闭
		CTSTPlugState=0;//将有线电视机顶盒插口状态置为0，表示断电状态
	}
}

void NetPlug(int state)//宽带路由器与交换机、网络存储等网络设备插口开关函数
{
	if (state == 1)// 状态置为1表示插口通电
	{
		digitalWrite(plugs[4],LOW);//使用数字引脚7为低电平控制继电器引脚5，开关通电
		NetPlugState=1;//将插口状态置为1，表示通电状态
	}
	else//状态置为0表示插口断电
	{
		digitalWrite(plugs[4],HIGH);//使用数字引脚7为高电平控制继电器引脚5，开关关闭
		NetPlugState=0;//将插口状态置为0，表示断电状态
	}
}

void NetSTPlug(int state)//网络机顶盒插口开关函数
{
	if (state == 1)// 状态置为1表示插口通电
	{
		digitalWrite(plugs[5],LOW);//使用数字引脚8为低电平控制继电器引脚6，开关通电
		NetSTPlugState=1;//将插口状态置为1，表示通电状态
	}
	else//状态置为0表示插口断电
	{
		digitalWrite(plugs[5],HIGH);//使用数字引脚8为高电平控制继电器引脚6，开关关闭
		NetSTPlugState=0;//将插口状态置为0，表示断电状态
	}
}

void DiskPlayPlug(int state)//碟机（包括CD、DVD、唱盘等）插口开关函数
{
	if (state == 1)// 状态置为1表示插口通电
	{
		digitalWrite(plugs[6],LOW);//使用数字引脚3为低电平控制继电器引脚7，开关通电
		DiskPlayPlugState=1;//将插口状态置为1，表示通电状态
	}
	else//状态置为0表示插口断电
	{
		digitalWrite(plugs[6],HIGH);//使用数字引脚3为高电平控制继电器引脚7，开关关闭
		DiskPlayPlugState=0;//将插口状态置为0，表示断电状态
	}
}

void otherPlug(int state)//其他插口开关函数
{
	if(state==1)//状态置为1表示插口通电
	{
		digitalWrite(plugs[7],LOW);//使用数字引脚9为低电平控制继电器引脚8，开关通电
		otherPlugState=1;//将插口状态置为1，表示通电状态
	}
	else
	{
		digitalWrite(plugs[7],HIGH);//使用数字引脚9为高电平控制继电器引脚8，开关关闭
		otherPlugState=0;//将插口状态置为0，表示断电状态
	}
}
/*---------以上定义了单个控制8个电源插口的命令函数------*/
/*---------以下定义了一个命令控制多个电源插口的命令函数--------*/

void playMusic(int state)//听，还是不听音乐就靠它了
{
	if(state==1)//如果状态置为1，表示要听音乐
	{
		if(StereoAMPPlugState == 0)//如果立体声功放没有打开
		{
			StereoAMPPlug(1);//打开立体声功放
		}		
		if(NetPlugState == 0)//如果网络设备没有打开
		{
			NetPlug(1);//打开网络设备
		}
		playMusicState=1;//将听音乐的状态置为1，表示正在听音乐
	}
	else//如果状态置为0，表示不想听音乐了!
	{
		if(TVPlugState ==0)//如果电视是关机状态
		{
			StereoAMPPlug(0);//那么就把立体声功放关闭
		}
		playMusicState=0;//将听音乐的状态置为0，表示不在听音乐
	}
}

void watchTV(int state)//由它来控制看还是不看电视
{
	if(state==1)//状态置为1表示要看电视了
	{
		if(TVPlugState!=1)//如果电视没有打开
		{
			TVPlug(1);
		}
		if(StereoAMPPlugState!=1)//如果立体声功放没有打开
		{
			StereoAMPPlug(1);//打开
		}
		if(AvAMPPlugState!=1)//如果AV功放没有打开
		{
			AvAMPPlug(1);//打开
		}
		if(CTSTPlugState!=1)//如果有线电视机顶盒没开
		{
			CTSTPlug(1);//打开
		}
		watchTVState=1;//标识为1，表示正在看电视节目
	}
	else//状态置为0,表示不想看电视了
	{
		if(NetSTPlugState==0 && DiskPlayPlugState==0 && playMusicState == 0)//判断下如果碟机并且网络机顶盒也是关闭的
		{
			TVPlug(0);//那么就说明现在没有要使用电视机的设备了，关闭电视
			AvAMPPlug(0);//关闭AV功放
			StereoAMPPlug(0);//关闭立体声
		}
		watchTVState=0;
	}
}

void watchAV(int state)//控制是否观看网络电视
{
	if(state == 1)//如果状态为1，表示要观看网络电视
	{
		if(CTSTPlugState!=1)
		{
			CTSTPlug(1);
		}
			
		if(TVPlugState!=1)//先看看电视有没有开，没开就打开
		{
			TVPlug(1);
		}
		if(StereoAMPPlugState!=1)//再看看立体声功放有没有开，没开也打开
		{
			StereoAMPPlug(1);
		}
		if(AvAMPPlugState!=1)//再看看AV功放开没，没开也打开
		{
			AvAMPPlug(1);
		}
		if(NetPlugState!=1)//看看网络设备还开了，没开也要打开
		{
			NetPlug(1);
		}
		NetSTPlug(1);//最后打开网络机顶盒
		watchAVstate=1;//把状态置为1，表示我正在看网络电视
	}
	else//如果状态为0，那就表示不想看网络电视了
	{
		NetSTPlug(0);//先把网络机顶盒关闭了
		delay(2000);//等10秒，安全关闭设备
		TVPlug(0);
		delay(2000);
		AvAMPPlug(0);
		delay(2000);
		if(watchTVState == 0 && playMusicState == 0)//如果现在有线电视并没有在播放中
		{
			StereoAMPPlug(0);//立体声也关闭
		}
		watchAVstate=0;//把网络电视的观看状态置0
	}
}

void closeAllPlug()//关闭所有的开关
{
	if(NetSTPlugState==1)//如果网络机顶盒是开的就关闭
	{
		NetSTPlug(0);
		delay(2000);//暂停10秒，待其安全关闭
	}
	if(DiskPlayPlugState==1)//如果碟机是开的就关闭
	{
		DiskPlayPlug(0);
		delay(2000);//暂停10秒，待其安全关闭
	}
	if(CTSTPlugState==1)//如果有线电视机顶盒是开的就关闭
	{
		CTSTPlug(0);
		delay(2000);//暂停10秒，待其安全关闭
	}
	if(TVPlugState==1)//如果电视机是开的就关闭
	{
		TVPlug(0);
		delay(2000);//电视机无所谓所以等1秒就可以了
	}
	if(AvAMPPlugState==1)//如果家庭影院功放是开的就关闭
	{
		AvAMPPlug(0);
		delay(2000);//停5秒，等它安全关闭
	}
	if(StereoAMPPlugState==1)//如果立体声功放是开的就关闭
	{
		StereoAMPPlug(0);
		delay(2000);//这个也等5秒
	}
	if(NetPlugState==1)//如果网络设备是开的也都关了
	{
		NetPlug(0);
		delay(1000);//等1秒应该够了
	}
	if(otherPlugState==1)
	{
		otherPlug(0);//不等了，插线板都呀关了
	}
}

void loop()
{
	while(Serial.available())//串口有数据的时候
	{
		contComm += char(Serial.read());//读取串口数据并加入到字符串变量中
		delay(2);//停顿一下等待接收，很关键不然数据收不全
	}
	if(contComm.length() > 0)//收到完整的字符串数据后
	{
		if(contComm == "TVup")
		{
			watchTV(1);//打开与看电视节目有关设备的插头
			Serial.println(contComm);
			contComm="";
		}
		if(contComm == "TVdown")
		{
			watchTV(0);//断开又关设备
			Serial.println(contComm);
			contComm="";
		}
		if(contComm == "AVup")
		{
			watchAV(1);//
			Serial.println(contComm);
			contComm="";
		}
		if(contComm == "AVdown")
		{
			watchAV(0);
			Serial.println(contComm);
			contComm="";
		}
		if(contComm == "DJup")
		{
			playMusic(1);
			Serial.println(contComm);
			contComm="";
		}
		if(contComm == "DJdown")
		{
			playMusic(0);
			Serial.println(contComm);
			contComm="";
		}
		if(contComm == "alldown")
		{
			closeAllPlug();
			Serial.println(contComm);
			contComm="";
		}
		if(contComm == "DVDup")
		{
			DiskPlayPlug(1);
			Serial.println(contComm);
			contComm="";
		}
		if(contComm == "DVDdown")
		{
			DiskPlayPlug(0);
			Serial.println(contComm);
			contComm="";
		}
		if(contComm == "USBup")
		{
			otherPlug(1);
			Serial.println(contComm);
			contComm="";
		}
		if(contComm == "USBdown")
		{
			otherPlug(0);
			Serial.println(contComm);
			contComm="";
		}
	}
}
