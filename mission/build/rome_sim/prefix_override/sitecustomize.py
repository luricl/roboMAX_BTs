import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/luricl/Documents/UnB/PIBIC/code/lab_samples_logistics/mission/install/rome_sim'
