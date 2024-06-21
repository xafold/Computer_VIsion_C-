#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/highgui/highgui.hpp>
#include <opencv4/opencv2/imgproc/imgproc.hpp>
#include <opencv4/opencv2/core/core.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(){
    Mat image1, image2;
    image1 = imread("/run/media/xafold/Games and Software/Task/utsavp/image_stitching/input/2.jpg"); // Query Image
    image2 = imread("/run/media/xafold/Games and Software/Task/utsavp/image_stitching/input/1.jpg"); // Train Image (image to be transformed)

    // Initializing the SIFT feature detector and extractor
    Ptr<SIFT> sift = SIFT::create();

    // Detecting the  keypoints and compute descriptors for both the input images
    vector<KeyPoint> keypoints1, keypoints2;
    Mat descriptors1, descriptors2;

    sift->detectAndCompute(image1, noArray(), keypoints1, descriptors1);
    sift->detectAndCompute(image2, noArray(), keypoints2, descriptors2);

    // Initializing the feature matcher using brute-force matching and matching the descriptor
    BFMatcher bf(NORM_L2, true);
    vector<DMatch> matches_bf;
    bf.match(descriptors1, descriptors2, matches_bf);

    // Sorting the matches by distance (lower distance are better)
    auto compareMatches = [](const DMatch& a, const DMatch& b) {
        return a.distance < b.distance;
    };

    sort(matches_bf.begin(), matches_bf.end(), compareMatches);

    // Drawing the top 40 matches
    int num_matches = 40;
    vector<char> matches_mask(matches_bf.size(), 0);  // Initializing the mask with zeros(for top 40 matches)
    for (int i = 0; i < num_matches; ++i) {
        matches_mask[i] = 1;
        }
    Mat image_matches_bf;
    drawMatches(image2, keypoints1, image1, keypoints2, matches_bf, image_matches_bf, Scalar::all(-1),
                    Scalar::all(-1), matches_mask, DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);


    // Extracting the matched keypoints
    vector<Point2f> source_points, destination_points;
    for (const DMatch& match : matches_bf) {
        source_points.push_back(keypoints1[match.queryIdx].pt);
        destination_points.push_back(keypoints2[match.trainIdx].pt);
    }

    // Converting keypoints to Matrix for findHomography function
    Mat src_points_mat(source_points);
    Mat dst_points_mat(destination_points);

    // Drawing the keypoints on both the input images
    Mat image1_keypoints, image2_keypoints;
    drawKeypoints(image1, keypoints1, image1_keypoints);
    drawKeypoints(image2, keypoints2, image2_keypoints);

    imwrite("/run/media/xafold/Games and Software/Task/utsavp/image_stitching/output/image_keypoint_1.png", image1_keypoints);
    imwrite("/run/media/xafold/Games and Software/Task/utsavp/image_stitching/output/image_keypoint_2.png", image2_keypoints);

    // Estimating the homography matrix using RANSAC algorithm
    Mat homography = findHomography(src_points_mat, dst_points_mat, RANSAC, 5.0);

    // Print out the homography matrix
    cout << "Estimated Homography Matrix:" << endl;
    for (int i = 0; i < homography.rows; ++i) {
        for (int j = 0; j < homography.cols; ++j) {
            cout << homography.at<double>(i, j) << " ";
        }
        cout << endl;
    }
    
    int width, height;
    width = image1.cols + image2.cols*0.8;
    height = image2.rows;

    Mat result = Mat::zeros(height, width, image1.type());

    // Applying the perspective transformation to train (transformed image) image
    warpPerspective(image1, result, homography, result.size());
    Mat result_stitch;
    result.copyTo(result_stitch);

    // Copying the contents of query image to the appropriate region in the result image
    Mat roi(result_stitch, Rect(0, 0, image2.cols, image2.rows));
    image2.copyTo(roi);

    // Check sizes before blending
    cout << "Size of result: " << result.size() << endl;
    cout << "Size of image2: " << image2.size() << endl;

    resize(image2, image2, result.size());
    double alpha = 0;
    Mat blended_image;
    addWeighted(result, alpha, image2, 1-alpha, 0, blended_image);

    imwrite("/run/media/xafold/Games and Software/Task/utsavp/image_stitching/output/brute_force_matched.png", image_matches_bf);
    imwrite("/run/media/xafold/Games and Software/Task/utsavp/image_stitching/output/homography_image.png", result);
    imwrite("/run/media/xafold/Games and Software/Task/utsavp/image_stitching/output/stitched_image1.png", result_stitch);
    imwrite("/run/media/xafold/Games and Software/Task/utsavp/image_stitching/output/blended_image1.png", blended_image);
    waitKey(0);
    destroyAllWindows();
    return 0;
}

