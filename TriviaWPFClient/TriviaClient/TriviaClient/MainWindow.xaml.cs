﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace TriviaClient
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private string username;
        private string password;

        public MainWindow()
        {
            InitializeComponent();

            
        }

        private void SignInClick(object sender, RoutedEventArgs e)
        {
            this.username = TBUsername.Text;
            this.password = TBPassword.Text;

            TBUsername.Text = "yay";
            TBPassword.Text = "yay";
        }
    }
}
