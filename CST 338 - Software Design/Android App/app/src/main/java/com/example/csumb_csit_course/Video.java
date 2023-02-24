package com.example.csumb_csit_course;
/*
 * Code to make the video display when the button "click here!" is clicked.
 */
import androidx.appcompat.app.AppCompatActivity;
import android.net.Uri;
import android.os.Bundle;
import android.widget.VideoView;

public class Video extends AppCompatActivity
{
    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_video);
        VideoView vidView = findViewById(R.id.videoView);
        //tracks the video's path and embeds it in code so that it plays in this new activity page.
        String path = "android.resource://com.example.csumb_csit_course/" + R.raw.video;
        Uri uri = Uri.parse(path);
        vidView.setVideoURI(uri); //sets the video to the uri so it displays
        vidView.start(); //starts the video
    }
}