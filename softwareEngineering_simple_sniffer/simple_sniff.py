# 2024-03-28
# This program predicts the number of active users in nearby space.
# this 'optimistically' predicts that a user is an active user device
# if it exchanges packets with the 'SKKU' ap even once, such as PROBE_REQUEST, etc...

# This works on ubuntu 18.04, python 3.6.9
# First of all, set up interface 'monitor'. (and write interface name to iface)
# Then run airodump-ng in other shell.
# Finally you can run this python source.

# sudo ifconfig wlp1s0 down
# sudo airmon-ng start wlp1s0
# sudo airodump-ng --essid SKKU --band abg  wlp1s0mon

from scapy.all import *
import time
import os
 
 # iface = input("Write interface:")
iface = "wlp1s0mon"
ap_list_SSID = [b"SKKU", b"1000", b"1000_2.4"]   # SSID (when release, only b"SKKU")
ap_list = []        # Mac address set of AP
users_list = {}     # (MAC of Users : Unix timestamp) set, i.e. we will use len(users_list)


def packethandler(pkt):
    if pkt.haslayer(Dot11):
        if pkt.type == 0 and pkt.subtype == 8:              # 802.11 frame type: Beacon
            if pkt.info in ap_list_SSID and pkt.addr2 not in ap_list:
                ap_list.append(pkt.addr2)
                print(f"AP MAC: {pkt.addr2} with SSID : {pkt.info}")

        elif pkt.addr2 in ap_list:                          # Other packets captured
            if pkt.addr1 != 'ff:ff:ff:ff:ff:ff':            # Broadcasting ignore
                users_list[pkt.addr1] = int(time.time())    # Unix time stamp
                print(ap_list)
                print(users_list)
                print(f"Current interactive users: {len(users_list)}")


# print(f"{pkt.addr1}") # Dst addr
# print(f"{pkt.addr2}") # src addr
# print(f"{pkt.addr3}") # BSSID (not used)

os.system("clear")
sniff(iface=iface, monitor=True, count=0, prn=packethandler)