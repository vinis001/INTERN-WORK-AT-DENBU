import re
from PIL import Image, ImageDraw, ImageFont
import qrcode
import pandas as pd
import csv
import serial
import os

ser = serial.Serial('COM7',57600)  

ser.write(b'r')


text = ser.readline().decode().strip()
print(text)

def generate_qr_with_counter(output_folder,extracted_text):
    global counter    
    
    qr_data =extracted_text
    
    qr = qrcode.QRCode(version=1, error_correction=qrcode.constants.ERROR_CORRECT_L, box_size=10, border=4)
    qr.add_data(qr_data)
    qr.make(fit=True)
    
    os.makedirs(output_folder, exist_ok=True)
    
    filename = f"{counter}.jpg"
    output_path = os.path.join(output_folder, filename)
    
    qr_img = qr.make_image()
    qr_img.save(output_path)
    
    #CALL THE OTHER FUNCTION TO ADD TEXT
    image_with_text = add_text_below_qr(qr_img, qr_data)
    image_with_text.save(output_path)
    return output_path

def add_text_below_qr(qr_img, qr_data):
    # Create a blank image with the same width as the QR code image
    width, height = qr_img.size
    image_with_text = Image.new('RGB', (width, height+50), color='white')
    image_with_text.paste(qr_img, (0, 0))
    draw = ImageDraw.Draw(image_with_text)
    font = ImageFont.truetype("Agdasima-Regular.ttf", 18)

    text = "Denbu Technology "+f"SNO={counter}"
    text_width, text_height = draw.textsize(text, font=font)
    text_x = (width - text_width) // 2
    text_y = height + 10
    draw.text((text_x, text_y), text, font=font, fill='black') 
    return image_with_text

def extract_text_between_delimiters(text):
    pattern = r"s:(.*):e"
    match = re.search(pattern, text)
    if match:
        extracted_text = match.group(1)
        return extracted_text.strip()
    else:
        return None

extracted_text = extract_text_between_delimiters(text)
if extracted_text:
    print("Extracted text:", extracted_text)

else:
    print("No match found.")

if "scale" in extracted_text:
  df1 = pd.read_csv("SCALE.csv")
  counter1 = df1['COUNTER'].iloc[-1]
  counter=counter1
  new_counter1=counter1+1
  from csv import writer
  List = [new_counter1]
  output_folder = r'C:\Users\Dell\Desktop\ARDUINO_QR\SCALE'
  with open('SCALE.csv', 'a') as f_object:
    writer_object = writer(f_object)
    writer_object.writerow(List)
    f_object.close()
    generate_qr_with_counter(output_folder,extracted_text)
    

elif "pipe" in extracted_text:
  df = pd.read_csv("PIPE.csv")
  counter2 = df['COUNTER'].iloc[-1]
  counter=counter2
  new_counter2=counter2+1
  from csv import writer
  List = [new_counter2]
  output_folder = r'C:\Users\Dell\Desktop\ARDUINO_QR\PIPE'
  with open('PIPE.csv', 'a') as f_object:
    writer_object = writer(f_object)
    writer_object.writerow(List)
    f_object.close()
    generate_qr_with_counter(output_folder,extracted_text)





