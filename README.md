# PTEase: Objective Airway Examination for Pulmonary Telemedicine using Commodity Smartphones
## Introduction
PTEase is a new smartphone-based sensing system designed to examine human airway's internal physiological conditions. PTEase uses active acoustic sensing to measure the internal changes of airway caliber, and then leverages machine learning to analyze the sensory data for pulmonary disease evaluation.
## Documentation
```
docs
+-- handouts: Experiment protocal and app instructions
+-- handouts_additional_notes: Notes for data quality control
```
## Source Code
```
src
+-- android: Android app
|   +-- ...
+-- data_processing: Server-side data processing writen in MATLAB
|   +-- ...
```
## 3D-Printing Files
```
3D-files
+-- adapters: Smartphone adapters
|   +-- Adapter_OnePlus7Pro.stl
|   +-- Adapter_S8.stl
+-- mouthpieces: Ergonomic mouthpieces of difference sizes
|   +-- mouthpiece_50.stl
|   +-- mouthpiece_75.stl
|   +-- mouthpiece_90.stl
|   +-- mouthpiece_100.stl
+-- realistic: Realistic human airway models
|   +-- trachea_0.8_connector.stl
|   +-- trachea_0.9_connector.stl
|   +-- trachea_connector.stl
|   +-- upper_airway.stl
```
## The dataset and example of using the dataset can be found here:
https://huggingface.co/datasets/ericyxy98/AWARE

## Demo Video can be found here:
https://drive.google.com/file/d/1xmYa-4QCGcroQQrfteDYuQvqz49G-79b/view?usp=share_link
