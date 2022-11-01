# Smart-Toy
STM32 동호회] 개인프로젝트 2 - Smart Toy

- **개발 필요성 :** 아이가 스마트 장난감을 이용하여 지적,신체적 능력과 흥미를 유발시키기 위해
제작하였습니다.

- **개발 목표 :**

       ① 장애물을 설치 시 Step motor와 gyro센서, IR센서를 이용하여 스마트 장난감이 장애물을   

            피하며, 아이의 지적,신체적 능력을 향상 시켜줌.
       ② Blue Tooth와 Buzzer를 이용하여 아이에게 흥미를 줌.

- **개발 기간 :** 2016. 10. 01 ~ 2016. 12. 30 (약 3개월)
- **개발 언어 및 환경 :** C/C++ / Windows 7 (64bit) / Keil_v5 / MCU(STM32F103CBT6)
- **개발 내용 :**

      1) **BlueTooth(모드선택) :** 스마트폰을 이용하여 조작가능

      2) **Gyro Sensor :** 기울기를 측정하여 스마트 장난감 회전시 위치를 잡아주는 역할의 센서

      3) **Stepmotor :** 스마트 장난감을 움직이게 하는 센서

      4) **IR Sensor :** 스마트 장난감의 주변 벽을 측정하는 센서

      5) **Buzzer Sensor :** 스마트 장난감 시작 및 종료를 소리로 나타내는 센서

- **구현 기술 :**

        1) **Blue Tooth : Blue Tooth, UART Interface**

           □ 용도
                ▶ 블루투스 모듈을 활용하여 스마트폰으로 스마트 장난감을 제어
           □ 기술내용
                ▶ 블루투스 모듈과 MCU간 인터페이스
                ▶ Interrupt를 이용한 양방향 UART 통신 프로그램 작성

        2) **Gyro Sensor : 3축 각도, 가속도 측정 센서, I2C Interface**

           □ 용도
              ▶ I2C 기능을 이용하여 Gyro Sensor가 측정한 Gyro x, y, z 3축값과 온도 값을 MCU로 전송
           □ 기술내용
              ▶ 디지털 센서와 MCU간 인터페이스에 많이 사용되고 있는 I2C 인터페이스 구현
              ▶ I2C 기능을 지원하는 센서 또는 칩 활용 기술 (비트 단위 직렬 전송 구현)

         3) **Step Motor : Step Motor, PWM**

           □ 용도
              ▶ PWM 제어를 이용한 Step Motor 제어
           □ 기술내용
              ▶ PWM을 이용한 모터 제어

         4) **IR Sensor : 적외선 센서, DMA, ADC**

           □ 용도
              ▶ DMA의 ADC를 이용하여 IR의 아날로그 값을 디지털 값으로 환산
           □ 기술내용
              ▶ 환산된 IR의 값을 테이블의 값으로 환산하여 적외선 센서의 값을 계산
              ▶ IR 센서와 MCU간 인터페이스