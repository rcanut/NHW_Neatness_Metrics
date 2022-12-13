# NHW Neatness Metrics

This metrics allows to compare neatness between 2 files based on a neatness/perceived quality model.

This work was initially done for the NHW Project (image compression codec) to objectively measure/show that
the codec has more neatness, compared to x265 (HEVC) for example.


## Usage

nhw_neatness_metrics.exe neatness_file.bmp reference_file.bmp [metric_visualization_file.bmp]
		
with neatness_file and reference_file bitmap color 512x512 images
		
Be sure neatness_file.bmp, the file to be studied is in first argument
and reference_file.bmp the original reference file is in second argument.

### Demo: 

metric_visualization_file on Lena.bmp

![Example 1](https://user-images.githubusercontent.com/12370082/207364918-157ff7f7-95c3-43a6-9e5b-0139c5430b81.png)
