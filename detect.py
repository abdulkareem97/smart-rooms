import cv2
import matplotlib.pyplot as plt
import pyttsx3
engine = pyttsx3.init()
config_file = 'ssd_mobilenet_v3_large_coco_2020_01_14.pbtxt.txt'
frozen_model = 'frozen_inference_graph.pb'
model = cv2.dnn_DetectionModel(frozen_model,config_file)
model.setInputSize(320,320)
model.setInputScale(1.0/127.5)
model.setInputMean((127.5,127.5,127.5))
model.setInputSwapRB(True)
text = ""
onLight = True


cap = cv2.VideoCapture(0)
while True:
    ret,frame = cap.read()
    index,confidence,box = model.detect(frame,confThreshold=0.5)
    if len(index)!=0 and (1 in index):

        onLight = True
        for student,conf,boxes in zip(index.flatten(),confidence.flatten(),box):
            if(student==1):
                
                print(student)
                cv2.rectangle(frame,boxes,(255,0,0),2)
    elif onLight:
        text = 'turn of ligth and fans'
        print('turn of ligth and fans')
        onLight = False
        engine.say(text)
        engine.runAndWait()
    else:
        print("nothing")


        
  


    cv2.imshow('Person in class',frame)
    if cv2.waitKey(2) and 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()