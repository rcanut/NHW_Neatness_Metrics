/***************************************************************************
****************************************************************************
*  NHW Neatness Metrics 												   *
*  file: nhw_neatness_metrics.c  										   *
*  version: 0.1.0 						     		     				   *
*  last update: $ 10152018 nhw exp $							           *
*																		   *
****************************************************************************
****************************************************************************

****************************************************************************
*  remark: -simple neatness metrics										   *
***************************************************************************/

#include <stdio.h>
#include <stdlib.h>

void main(int argc, char **argv) 
{	
	int i,j,scan,res,res2,n1,comp,NHW_IM_DIM=512,NHW_IM_SIZE=NHW_IM_DIM*NHW_IM_DIM,RGB_comps=3;
	int NEATNESS_PERCEPTION,NEATNESS_THRESHOLD1,NEATNESS_THRESHOLD2,CONTOURS,neatness_amount,significance;
	float neatness;
	unsigned char bmp_header[54],*nhw_image,*nhw_comp,*ref_image,*ref_comp;
	FILE *nhw_im_512,*ref_im_512;
	
	nhw_image=(unsigned char*)malloc(NHW_IM_SIZE*RGB_comps*sizeof(char));
	nhw_comp=(unsigned char*)malloc(NHW_IM_SIZE*sizeof(char));
	ref_image=(unsigned char*)malloc(NHW_IM_SIZE*RGB_comps*sizeof(char));
	ref_comp=(unsigned char*)malloc(NHW_IM_SIZE*sizeof(char));

	if (argv[1]==NULL || argv[1]==0)
	{
		printf("\n Copyright (C) 2018 NHW Neatness Metrics\n");
		printf("\n nhw_neatness_metrics.exe neatness_file.bmp reference_file.bmp");
		printf("\n (with neatness_file and reference_file bitmap color 512x512 images)\n");
		exit(-1);
	}

	if ((nhw_im_512 = fopen(argv[1],"rb")) == NULL )
	{
		printf ("\n Could not open neatness file \n");
		exit(-1);
	}
	
	fread(bmp_header,54,1,nhw_im_512);
	
	fread(nhw_image,NHW_IM_SIZE*RGB_comps,1,nhw_im_512);
	
	fclose(nhw_im_512);
	
	if ((ref_im_512 = fopen(argv[2],"rb")) == NULL )
	{
		printf ("\n Could not open reference file \n");
		exit(-1);
	}
	
	fread(bmp_header,54,1,ref_im_512);
	
	fread(ref_image,NHW_IM_SIZE*RGB_comps,1,ref_im_512);
	
	fclose(ref_im_512);
	
	// Start processing
	
	NEATNESS_PERCEPTION=160;
	NEATNESS_THRESHOLD1=30;
	NEATNESS_THRESHOLD2=3;
	CONTOURS=14;
	
	for (comp=0,significance=0,n1=0,neatness_amount=0;comp<RGB_comps;comp++)
	{
	
		for (i=0,j=0;i<(NHW_IM_SIZE*RGB_comps);i+=RGB_comps,j++)
		{
			nhw_comp[j]=nhw_image[i+comp];
			ref_comp[j]=ref_image[i+comp];
		}
		
	
		for (i=NHW_IM_DIM,res=0;i<(NHW_IM_SIZE-NHW_IM_DIM);i+=NHW_IM_DIM)
		{
			for (scan=i+1,j=1;j<(NHW_IM_DIM-1);j++,scan++)
			{   
				res	   =    (nhw_comp[scan]<<3) -
							nhw_comp[scan-1]-nhw_comp[scan+1]-
							nhw_comp[scan-NHW_IM_DIM]-nhw_comp[scan+NHW_IM_DIM]-
							nhw_comp[scan-(NHW_IM_DIM+1)]-nhw_comp[scan+(NHW_IM_DIM-1)]-
							nhw_comp[scan-(NHW_IM_DIM-1)]-nhw_comp[scan+(NHW_IM_DIM+1)];
					
				// If neatness pixel
				if (abs(res)>NEATNESS_PERCEPTION) 
				{
					// Detect contours
					if (abs(nhw_comp[scan]-nhw_comp[scan-1])<CONTOURS) n1++;
					if (abs(nhw_comp[scan]-nhw_comp[scan+1])<CONTOURS) n1++;
					if (abs(nhw_comp[scan]-nhw_comp[scan-NHW_IM_DIM])<CONTOURS) n1++;
					if (abs(nhw_comp[scan]-nhw_comp[scan-(NHW_IM_DIM+1)])<CONTOURS) n1++;
					if (abs(nhw_comp[scan]-nhw_comp[scan-(NHW_IM_DIM-1)])<CONTOURS) n1++;
					if (abs(nhw_comp[scan]-nhw_comp[scan+NHW_IM_DIM])<CONTOURS) n1++;
					if (abs(nhw_comp[scan]-nhw_comp[scan+(NHW_IM_DIM-1)])<CONTOURS) n1++;
					if (abs(nhw_comp[scan]-nhw_comp[scan+(NHW_IM_DIM+1)])<CONTOURS) n1++;
					
					// If contours
					if (n1>3)
					{
					
						// Compare neatness with reference image contours
						res2 =  (ref_comp[scan]<<3) -
								ref_comp[scan-1]-ref_comp[scan+1]-
								ref_comp[scan-NHW_IM_DIM]-ref_comp[scan+NHW_IM_DIM]-
								ref_comp[scan-(NHW_IM_DIM+1)]-ref_comp[scan+(NHW_IM_DIM-1)]-
								ref_comp[scan-(NHW_IM_DIM-1)]-ref_comp[scan+(NHW_IM_DIM+1)];
					
						if (abs(res2)>(NEATNESS_PERCEPTION>>1))
						{				
							if (res>0) 
							{
								if ((nhw_comp[scan]-ref_comp[scan])>=NEATNESS_THRESHOLD2 && (nhw_comp[scan]-ref_comp[scan])<=NEATNESS_THRESHOLD1)
								{
									neatness_amount += (nhw_comp[scan]-ref_comp[scan])*(nhw_comp[scan]-ref_comp[scan]);
									
									significance++;
								}
							}
							else
							{
								if ((ref_comp[scan]-nhw_comp[scan])>=NEATNESS_THRESHOLD2 && (ref_comp[scan]-nhw_comp[scan])<=NEATNESS_THRESHOLD1)
								{
									neatness_amount += (ref_comp[scan]-nhw_comp[scan])*(ref_comp[scan]-nhw_comp[scan]);
									
									significance++;
								}
							}
						}
					}
					
					n1=0;
				}					
			}
		}
	}
	
	neatness = (float)((float)(neatness_amount)/(float)(significance));
	
	printf("\nSignificance = %d  NHW Neatness metrics = %f\n",significance,neatness);
}
