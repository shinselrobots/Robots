//------------------------------------------------------------------------------
// <copyright file="MainWindow.xaml.cs" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
//------------------------------------------------------------------------------

namespace RobotKinectViewer
{
    using System;
    using System.Diagnostics;
    using System.Windows;
    using System.Windows.Documents;
    using System.Windows.Input;
    using Microsoft.Kinect;
    using RobotKinect.Speech;

     /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        #region Private state
        private readonly KinectSensorItems sensorItems;
 
        #endregion Private state

        #region ctor & Window events
        public MainWindow()
        {
            InitializeComponent();
            this.sensorItems = new KinectSensorItems();
            this.kinectSensors.ItemsSource = this.sensorItems;
            // DAVES> Minimize Kinect Device selection window on startup
            this.WindowState = System.Windows.WindowState.Minimized;
        }

        private void WindowLoaded(object sender, EventArgs e)
        {
                 this.KinectStart();
        }

        private void WindowClosed(object sender, EventArgs e)
        {
            this.KinectStop();
        }
        #endregion ctor & Window events

        #region Multi-Kinect discovery + setup
        private void KinectStart()
        {
            // listen to any status change for Kinects.
            KinectSensor.KinectSensors.StatusChanged += this.KinectsStatusChanged;
            bool nGoodKinectSensorFound = false;
            // show status for each sensor that is found now.
            foreach (KinectSensor kinect in KinectSensor.KinectSensors)
            {
                this.ShowStatus(kinect, kinect.Status);
                if (kinect.Status == KinectStatus.Connected)
                {
                    nGoodKinectSensorFound = true;
                }
            }
            if (!nGoodKinectSensorFound)
            {
                // DAVES> Restore Kinect Device selection window if no device or error
                this.WindowState = System.Windows.WindowState.Normal;
            }
        }

        private void KinectStop()
        {
            foreach (KinectSensorItem sensorItem in this.sensorItems)
            {
                var kinectWindow = sensorItem.Window;
                if (kinectWindow != null)
                {
                    kinectWindow.Kinect = null;
                    kinectWindow.Close();
                }
            }

            this.sensorItems.Clear();
        }

        private void ShowStatus(KinectSensor kinectSensor, KinectStatus kinectStatus)
        {
            sensorStatusChanges.Text += kinectSensor.DeviceConnectionId + " " + kinectStatus + "\n";

            KinectSensorItem sensorItem;
            this.sensorItems.SensorLookup.TryGetValue(kinectSensor, out sensorItem);
            switch (kinectStatus)
            {
                case KinectStatus.Disconnected:
                case KinectStatus.NotPowered:
                    if (sensorItem != null)
                    {
                        this.sensorItems.Remove(sensorItem);
                        if (sensorItem.Window != null)
                        {
                            sensorItem.Window.Close();
                            sensorItem.Window = null;
                        }
                    }

                    break;
                default:
                    if (sensorItem == null)
                    {
                        sensorItem = new KinectSensorItem
                        {
                            Window = null,
                            Sensor = kinectSensor,
                            Status = kinectSensor.Status
                        };
                        this.sensorItems.Add(sensorItem);
                    }

                    // show a window, if one isn't already shown, unless we are initializing
                    if (sensorItem.Window == null && kinectStatus != KinectStatus.Initializing)
                    {
                        var kinectWindow = new KinectWindow { Kinect = kinectSensor };
                        kinectWindow.Show();

                        sensorItem.Window = kinectWindow;
                    }

                    if (sensorItem.Window != null)
                    {
                        sensorItem.Window.StatusChanged();
                    }

                    sensorItem.Status = kinectStatus;
                    break;
            }
        }

        private void KinectsStatusChanged(object sender, StatusChangedEventArgs e)
        {
            this.ShowStatus(e.Sensor, e.Status);
        }
        #endregion Multi-Kinect discovery + setup

        #region UI event handlers
        private void ShowMoreInfo(object sender, RoutedEventArgs e)
        {
            Hyperlink hyperlink = e.OriginalSource as Hyperlink;
            if (hyperlink != null)
            {
                // Careful - ensure that this NavigateUri comes from a trusted source, as in this sample, before launching a process using it.
                Process.Start(new ProcessStartInfo(hyperlink.NavigateUri.ToString()));
            }

            e.Handled = true;
        }

        // if you mousedown with a control key pressed down, it will try to begin execution again...as if it was a fresh startup.
        // likely not useful to include in the tool, once we fix bugs.
        private void GridMouseDown(object sender, MouseEventArgs e)
        {
            if (Keyboard.IsKeyDown(Key.LeftCtrl) || Keyboard.IsKeyDown(Key.RightCtrl))
            {
                this.KinectStop();
                this.KinectStart();
            }
        }
        #endregion UI event handlers
    }
}

