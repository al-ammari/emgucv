//----------------------------------------------------------------------------
//
//  Copyright (C) 2004-2011 by EMGU. All rights reserved.
//
//----------------------------------------------------------------------------

#include "opencv2/gpu/gpu.hpp"

CVAPI(cv::gpu::SURF_GPU*) gpuSURFDetectorCreate(double _hessianThreshold, int _nOctaves, int _nOctaveLayers, bool _extended, float _keypointsRatio)
{
   return new cv::gpu::SURF_GPU(_hessianThreshold, _nOctaves, _nOctaveLayers, _extended, _keypointsRatio);
}

CVAPI(void) gpuSURFDetectorRelease(cv::gpu::SURF_GPU** detector)
{
   delete *detector;
}

CVAPI(void) gpuSURFDetectorDetectKeyPoints(cv::gpu::SURF_GPU* detector, const cv::gpu::GpuMat* img, const cv::gpu::GpuMat* mask, cv::gpu::GpuMat* keypoints)
{
   (*detector)(*img, mask ? *mask : cv::gpu::GpuMat() , *keypoints);
}

CVAPI(void) gpuDownloadKeypoints(cv::gpu::SURF_GPU* detector, const cv::gpu::GpuMat* keypointsGPU, std::vector<cv::KeyPoint>* keypoints)
{
   detector->downloadKeypoints(*keypointsGPU, *keypoints);
}

CVAPI(void) gpuUploadKeypoints(cv::gpu::SURF_GPU* detector, const std::vector<cv::KeyPoint>* keypoints, cv::gpu::GpuMat* keypointsGPU)
{
   detector->uploadKeypoints(*keypoints, *keypointsGPU);
}

CVAPI(void) gpuSURFDetectorCompute(
   cv::gpu::SURF_GPU* detector, 
   const cv::gpu::GpuMat* img, 
   const cv::gpu::GpuMat* mask, 
   cv::gpu::GpuMat* keypoints, 
   cv::gpu::GpuMat* descriptors, 
   bool useProvidedKeypoints)
{
   (*detector)(
      *img, 
      mask? *mask : cv::gpu::GpuMat(), 
      *keypoints,
      *descriptors,
      useProvidedKeypoints);
}

CVAPI(int) gpuSURFDetectorGetDescriptorSize(cv::gpu::SURF_GPU* detector)
{
   return detector->descriptorSize();
}