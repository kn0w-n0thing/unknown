import netifaces

for interface in netifaces.interfaces():
	if interface == 'enp2s0':
		try:
			print(str(netifaces.ifaddresses(interface)[netifaces.AF_INET][0]['addr']))
			break
		except:
			pass
	elif interface == 'wlp1s0':
		try:
			print(str(netifaces.ifaddresses(interface)[netifaces.AF_INET][0]['addr']))
			break		
		except:
			pass
		break
	elif interface == 'wlp2s0':
		try:
			print(str(netifaces.ifaddresses(interface)[netifaces.AF_INET][0]['addr']))
			break
		except:
			pass