# sudo ifconfig wlp1s0 down
# sudo airmon-ng start wlp1s0
# sudo airodump-ng --essid 1000 --band abg  wlp1s0mon

from scapy.all import *

def packet_callback(packet):
    # 패킷 처리 로직 작성
    print(packet.show())
    
    # print("HELLO:::: ", packet.info)
    pass

# 캡처할 패킷의 필터링 조건을 설정합니다.
# filter_condition = "ether src host 11:22:33:44:55:66"
filter_condition = ""

# 네트워크 인터페이스를 선택합니다.
iface = "wlp1s0mon"

# 패킷 캡처를 시작합니다.
sniff(iface=iface, filter=filter_condition, monitor=True, prn=packet_callback)