# NHW Neatness Metrics

This metrics allows to compare neatness between 2 files based on a neatness/perceived quality model.

This work was initially done for the NHW Project (image compression codec) to objectively measure/show that
the codec has more neatness, compared to x265 (HEVC) for example.


## Usage

nhw_neatness_metrics.exe neatness_file.bmp reference_file.bmp
		
with neatness_file and reference_file bitmap color 512x512 images
		
Be sure neatness_file.bmp, the file to be studied is in first argument
and reference_file.bmp the original reference file is in second argument.
