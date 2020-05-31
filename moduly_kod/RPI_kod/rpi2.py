from re import search
from serial import Serial
from subprocess import run
from time import sleep


def main():
    data = get_data_from_serial()
    if data is not None:
        formatted_data = format_data(data)
        send_data(formatted_data)


def send_data(data):
    if data:
        for k, v in data.items():
            run(["curl", "-i", "-XPOST", "http://40.114.77.143:8086/write?db=dane", "--data-binary",
                 "{},host=admin value={}".format(k, v)], shell=False)
            sleep(2)


def get_data_from_serial():
    s = Serial("/dev/ttyACM0", 9600, timeout=1)
    s.flush()
    data = s.readline().decode("utf-8").rstrip()
    if data != "":
        return data
    else:
        return None


def format_data(data):
    formatted_data = dict()
    if "HC12" in data:
        hc_12_data = search("(?<=HC12).....", data).group()
        formatted_data["salon"] = hc_12_data
    if "LORA" in data:
        lora_data = search("(?<=LORA).....", data).group()
        formatted_data["kuchnia"] = lora_data
    if "NRF24L01" in data:
        nrf24l01_data = search("(?<=NRF24L01).....", data).group()
        formatted_data["garaz"] = nrf24l01_data
    if "XBEE" in data:
        xbee_data = search("(?<=XBEE).....", data).group()
        formatted_data["lazienka"] = xbee_data
    return formatted_data


if __name__ == "__main__":
    counter = 0
    while True:
        try:
            main()
        except:
            counter += 1
            if counter <= 10:
                continue
            else:
                run(["sudo", "reboot"])
