String contComm="";//收集串口发出的命令标签，用于串口控制
int plugs[8] = {2,3,4,5,6,7,8,9};//分配控制插座的开关引脚
int plugstate[8];//用来记录插口电平，LOW就是低电平为0，HIGH高电平为1
int stopTime[8] = {200,200,200,2000,200,2000,200,200};//这个数组用来配置等待时间，由于电脑或者小盒子等主机类设备会有开关机时间所以插口等待时间需要长点！

void setup()
{
	for(int i=0;i<8;i++)//初始化数字引脚2-9为高电平，控制8个继电器状态为关闭
	{
		pinMode(plugs[i],OUTPUT);//引脚为输出
		digitalWrite(plugs[i],HIGH);//引脚为高电平
		plugstate[i]= HIGH; //状态置1
	}
	Serial.begin(9600);//打开串口通讯
}

void plugContral(int plugNum,char state)//插口控制函数，带2个参数，插口编号从0-7，状态为LOW或HIGH
{
	digitalWrite(plugs[plugNum],state);//按参数控制数字插口
	plugstate[plugNum] = state;//在插口数组中写入状态，LOW是0，HIGH是1
	delay(stopTime[plugNum]);//按数组中相应值停留一会
	for(int i=0;i<8;i++)
	{
		Serial.print(plugstate[i]);
	}
}

void playMusic(int state)//听，还是不听音乐就靠它了
{
	if(state==1)//如果状态置为1，表示要听音乐
	{
		if(plugstate[1] == 1)//如果立体声功放没有打开
		{
			plugContral(1,LOW);//打开立体声功放
		}		
		if(plugstate[5] == 1)//如果网络设备没有打开
		{
			plugContral(5,LOW);//打开网络设备
		}
	}
	else//如果状态置为0，表示不想听音乐了!
	{
		plugContral(5,HIGH);//关闭网络设备
		if(plugstate[0] == 1)//如果电视是关机状态
		{
			plugContral(1,HIGH);//那么就把立体声功放关闭
		}
	}
}

void watchTV(int state)//由它来控制看还是不看电视
{
	if(state==1)//状态置为1表示要看电视了
	{
		if(plugstate[0] == 1)//如果电视没有打开
		{
			plugContral(0,LOW);
		}
		if(plugstate[1] == 1)//如果立体声功放没有打开
		{
			plugContral(1,LOW);//打开
		}
		if(plugstate[2] == 1)//如果AV功放没有打开
		{
			plugContral(2,LOW);//打开
		}
		if(plugstate[3] == 1)//如果有线电视机顶盒没开
		{
			plugContral(3,LOW);//打开
		}
	}
	else//状态置为0,表示不想看电视了
	{
		if(plugstate[4] == 1 && plugstate[6] == 1)//判断下如果碟机和网络机顶盒也是关闭的
		{
			for(int i=3;i>=0;i--)plugContral(i,HIGH);
		}
	}
}

void watchAV(int state)//控制是否观看网络电视
{
	if(state == 1)//如果状态为1，表示要观看网络电视
	{
		if(plugstate[3] == 1)
		{
			plugContral(3,LOW);
		}
			
		if(plugstate[0] == 1)//先看看电视有没有开，没开就打开
		{
			plugContral(0,LOW);
		}
		if(plugstate[1] == 1)//再看看立体声功放有没有开，没开也打开
		{
			plugContral(1,LOW);
		}
		if(plugstate[2] == 1)//再看看AV功放开没，没开也打开
		{
			plugContral(2,LOW);
		}
		if(plugstate[5] == 1)//看看网络设备还开了，没开也要打开
		{
			plugContral(5,LOW);
		}
		plugContral(4,LOW);//最后打开网络机顶盒
	}
	else//如果状态为0，那就表示不想看网络电视了
	{
		for(int i=5;i >= 0;i--)plugContral(i,HIGH);
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
			for(int i=0;i<8;i++)
			{
				plugContral(i,HIGH);
			}
			Serial.println(contComm);
			contComm="";
		}
		if(contComm == "DVDup")
		{
			plugContral(6,LOW);
			Serial.println(contComm);
			contComm="";
		}
		if(contComm == "DVDdown")
		{
			plugContral(6,HIGH);
			Serial.println(contComm);
			contComm="";
		}
		if(contComm == "USBup")
		{
			plugContral(7,LOW);
			Serial.println(contComm);
			contComm="";
		}
		if(contComm == "USBdown")
		{
			plugContral(7,HIGH);
			Serial.println(contComm);
			contComm="";
		}
	}
}
