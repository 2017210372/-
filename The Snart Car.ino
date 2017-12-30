#include <Servo.h> 
int Echo = 10;  // Echo������(P2.0)
int Trig =11;  //  Trig ������(P2.1)

int Distance = 0;
int Left_motor_go=8;     //����ǰ��(IN1)
int Left_motor_back=9;     //��������(IN2)
int Right_motor_go=10;    // �ҵ��ǰ��(IN3)
int Right_motor_back=11;    // �ҵ������(IN4)
int key=A2;//���尴�� A2 �ӿ�
int beep=A3;//��������� A3 �ӿ�
void setup()
{
  Serial.begin(9600);     // ��ʼ������
  //��ʼ���������IOΪ�����ʽ
  pinMode(Left_motor_go,OUTPUT); // PIN 8 (PWM)
  pinMode(Left_motor_back,OUTPUT); // PIN 9 (PWM)
  pinMode(Right_motor_go,OUTPUT);// PIN 10 (PWM) 
  pinMode(Right_motor_back,OUTPUT);// PIN 11 (PWM)
  pinMode(key,INPUT);//���尴���ӿ�Ϊ����ӿ�
  pinMode(beep,OUTPUT);
  pinMode(Echo, INPUT);    // ���峬���������
  pinMode(Trig, OUTPUT);   // ���峬���������
}
void run()     // ǰ��
{
  digitalWrite(Right_motor_go,HIGH);  // �ҵ��ǰ��
  digitalWrite(Right_motor_back,LOW);     
  analogWrite(Right_motor_go,150);//0~255���٣������ֲ���������
  analogWrite(Right_motor_back,0);
  digitalWrite(Left_motor_go,LOW);  // ����ǰ��
  digitalWrite(Left_motor_back,HIGH);
  analogWrite(Left_motor_go,0);//PWM����0~255���٣������ֲ���������
  analogWrite(Left_motor_back,150);
}
void brake(int time)  //ɲ����ͣ��
{
  digitalWrite(Right_motor_go,LOW);
  digitalWrite(Right_motor_back,LOW);
  digitalWrite(Left_motor_go,LOW);
  digitalWrite(Left_motor_back,LOW);
  delay(time * 100);//ִ��ʱ�䣬���Ե���  
}
void left()         //��ת(���ֲ���������ǰ��)
{
  digitalWrite(Right_motor_go,HIGH);	// �ҵ��ǰ��
  digitalWrite(Right_motor_back,LOW);
  analogWrite(Right_motor_go,150); 
  analogWrite(Right_motor_back,0);//PWM����0~255����
  digitalWrite(Left_motor_go,LOW);   //���ֺ���
  digitalWrite(Left_motor_back,LOW);
  analogWrite(Left_motor_go,0); 
  analogWrite(Left_motor_back,0);//PWM����0~255����
}

void spin_left(int time)         //��ת(���ֺ��ˣ�����ǰ��)
{
  digitalWrite(Right_motor_go,HIGH);	// �ҵ��ǰ��
  digitalWrite(Right_motor_back,LOW);
  analogWrite(Right_motor_go,150); 
  analogWrite(Right_motor_back,0);//PWM����0~255����
  digitalWrite(Left_motor_go,HIGH);   //���ֺ���
  digitalWrite(Left_motor_back,LOW);
  analogWrite(Left_motor_go,150); 
  analogWrite(Left_motor_back,0);//PWM����0~255����
  delay(time * 100);	//ִ��ʱ�䣬���Ե���  
}

void right(int time)
{
  digitalWrite(Right_motor_go,LOW);   //�ҵ������
  digitalWrite(Right_motor_back,LOW);
  analogWrite(Right_motor_go,0); 
  analogWrite(Right_motor_back,0);//PWM����0~255����
  digitalWrite(Left_motor_go,LOW);//����ǰ��
  digitalWrite(Left_motor_back,HIGH);
  analogWrite(Left_motor_go,0); 
  analogWrite(Left_motor_back,150);//PWM����0~255����
  delay(time * 100);	//ִ��ʱ�䣬���Ե���  
}
void spin_right(int time)        //��ת(���ֺ��ˣ�����ǰ��)
{
  digitalWrite(Right_motor_go,LOW);   //�ҵ������
  digitalWrite(Right_motor_back,HIGH);
  analogWrite(Right_motor_go,0); 
  analogWrite(Right_motor_back,150);//PWM����0~255����
  digitalWrite(Left_motor_go,LOW);//����ǰ��
  digitalWrite(Left_motor_back,HIGH);
  analogWrite(Left_motor_go,0); 
  analogWrite(Left_motor_back,150);//PWM����0~255����
  delay(time * 100);	//ִ��ʱ�䣬���Ե���        
}

void back(int time)          //����
{
  digitalWrite(Right_motor_go,LOW);  //���ֺ���
  digitalWrite(Right_motor_back,HIGH);
  analogWrite(Right_motor_go,0);
  analogWrite(Right_motor_back,150);//PWM����0~255����
  digitalWrite(Left_motor_go,HIGH);  //���ֺ���
  digitalWrite(Left_motor_back,LOW);
  analogWrite(Left_motor_go,150);
  analogWrite(Left_motor_back,0);//PWM����0~255����
  delay(time * 100);     //ִ��ʱ�䣬���Ե���   
}
void keysacn()//����ɨ��
{
  int val;
  val=digitalRead(key);//��ȡ����7 �ڵ�ƽֵ����val
  while(!digitalRead(key))//������û������ʱ��һֱѭ��
  {
    val=digitalRead(key);//�˾��ʡ�ԣ�����ѭ���ܿ�
  }
  while(digitalRead(key))//������������ʱ
  {
    delay(10);	//��ʱ10ms
    val=digitalRead(key);//��ȡ����7 �ڵ�ƽֵ����val
    if(val==HIGH)  //�ڶ����жϰ����Ƿ񱻰���
    {
      digitalWrite(beep,HIGH);		//��������
      while(!digitalRead(key))	//�жϰ����Ƿ��ɿ�
        digitalWrite(beep,LOW);		//������ֹͣ
    }
    else
      digitalWrite(beep,LOW);          //������ֹͣ
  }
}

void Distance_test()   // ����ǰ������ 
{
  digitalWrite(Trig, LOW);   // �������ŵ͵�ƽ2��s
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);  // �������Ÿߵ�ƽ10��s������������10��s
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);    // �����������ŵ͵�
  float Fdistance = pulseIn(Echo, HIGH);  // ��ȡ�ߵ�ƽʱ��(��λ��΢��)
  Fdistance= Fdistance/58;       //Ϊʲô����58�������ף�  Y��=��X��*344��/2
  // X��=�� 2*Y�ף�/344 ==��X��=0.0058*Y�� ==������=΢��/58
  Serial.print("Distance:");      //������루��λ�����ף�
  Serial.println(Fdistance);         //��ʾ����
  Distance = Fdistance;
}  
void loop()
{
  keysacn();	   //���ð���ɨ�躯��
  while(1)
  {
    Distance_test();//����ǰ������
    if(Distance < 40)//��ֵΪ�����ϰ���ľ��룬���԰�ʵ���������
      while(Distance < 40)//�ٴ��ж��Ƿ����ϰ��������ת������󣬼����ж�
      {
        back(2);        
        right(1);//��ת
        digitalWrite(beep,HIGH);          //������ֹͣ
       brake(1);//ͣ��
        Distance_test();//����ǰ������
       }
    else
      {
        run();//���ϰ��ֱ��
        digitalWrite(beep,LOW);  
      }
  }
}









