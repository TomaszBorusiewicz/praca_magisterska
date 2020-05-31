import random
from datetime import datetime


class IotSimulator:

    def simulate_data(self):
        current_hour = datetime.now().hour
        hc12 = self.get_hc12_value(current_hour)
        lora = self.get_lora_value(current_hour)
        xbee = self.get_xbee_value(current_hour)
        nrf24l01 = self.get_nrf24l01_value(current_hour)
        return hc12 + nrf24l01 + lora + xbee

    def get_hc12_value(self, current_hour):
        value = None
        if 12 > current_hour >= 10:
            value = round(random.uniform(21.00, 21.30), 2)
        elif 18 > current_hour >= 12:
            value = round(random.uniform(23.00, 23.30), 2)
        elif 24 > current_hour >= 18:
            value = round(random.uniform(22.00, 22.30), 2)
        elif 10 > current_hour >= 0:
            value = round(random.uniform(18.00, 18.30), 2)
        value = "HC12" + str(value)
        if len(value.split(".")[-1]) == 1:
            value += "0"
        return value

    def get_nrf24l01_value(self, current_hour):
        value = None
        if 12 > current_hour >= 10:
            value = round(random.uniform(18.00, 18.30), 2)
        elif 18 > current_hour >= 12:
            value = round(random.uniform(19.00, 19.30), 2)
        elif 24 > current_hour >= 18:
            value = round(random.uniform(17.00, 17.30), 2)
        elif 10 > current_hour >= 0:
            value = round(random.uniform(17.00, 17.30), 2)
        value = "NRF24L01" + str(value)
        if len(value.split(".")[-1]) == 1:
            value += "0"
        return value

    def get_lora_value(self, current_hour):
        value = None
        if 12 > current_hour >= 10:
            value = round(random.uniform(21.00, 21.30), 2)
        elif 18 > current_hour >= 12:
            value = round(random.uniform(23.00, 23.30), 2)
        elif 24 > current_hour >= 18:
            value = round(random.uniform(21.00, 21.30), 2)
        elif 10 > current_hour >= 0:
            value = round(random.uniform(18.00, 18.30), 2)
        value = "LORA" + str(value)
        if len(value.split(".")[-1]) == 1:
            value += "0"
        return value

    def get_xbee_value(self, current_hour):
        value = None
        if 12 > current_hour >= 10:
            value = round(random.uniform(22.00, 22.30), 2)
        elif 18 > current_hour >= 12:
            value = round(random.uniform(23.00, 23.30), 2)
        elif 24 > current_hour >= 18:
            value = round(random.uniform(24.00, 24.30), 2)
        elif 10 > current_hour >= 0:
            value = round(random.uniform(21.00, 21.30), 2)
        value = "XBEE" + str(value)
        if len(value.split(".")[-1]) == 1:
            value += "0"
        return value
