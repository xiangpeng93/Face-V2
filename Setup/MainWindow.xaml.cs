using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
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

namespace Setup
{
    /// <summary>
    /// MainWindow.xaml 的交互逻辑
    /// </summary>
    public partial class MainWindow : Window
    {
        /*
        FACEPLUS_API int testInt();
        FACEPLUS_API int testString(char *message);

        FACEPLUS_API int groupManger(int cmd, char * groupName);
        FACEPLUS_API int personManger(int cmd, char * personName, char* groupName, char * faceId);
        FACEPLUS_API int detectManger(char * url, char *result);
        FACEPLUS_API int trainManger(int cmd,char *name);
        FACEPLUS_API int recManger(int cmd, char *url, char *group, char *result);
        FACEPLUS_API int getMessage(char *message);
         * enum CMDLIST
        {
            _CREATE,
            _DELETE,
            _ADD,
            _REMOVE,
            _PERSON,
            _GROUP
        };
         */

        [DllImport("FacePlus.dll", EntryPoint = "groupManger", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        static extern Int32 groupManger(Int32 cmd, string groupName);

        [DllImport("FacePlus.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        static extern Int32 personManger(Int32 cmd,string personName, string groupName, string faceId);

        [DllImport("FacePlus.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        static extern int detectManger(string url, StringBuilder result);

        [DllImport("FacePlus.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        static extern Int32 trainManger(Int32 cmd, string name);

        [DllImport("FacePlus.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        static extern int recManger(Int32 cmd, string url, string group, StringBuilder result);

        [DllImport("FacePlus.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        static extern Int32 getMessage(StringBuilder message);

        [DllImport("FacePlus.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        static extern Int32 testInt();
        [DllImport("FacePlus.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        static extern Int32 testString(StringBuilder message);
        public MainWindow()
        {
            InitializeComponent();
        }

        private void AddGroup_Click(object sender, RoutedEventArgs e)
        {
            StringBuilder message = new StringBuilder(10*1024);
            groupManger(0, value_group_box.Text);
            getMessage(message);
            message_box.Text = message.ToString();

        }

        private void DeleteGroup_Click(object sender, RoutedEventArgs e)
        {
            StringBuilder message = new StringBuilder(10 * 1024);
            groupManger(1, value_group_box.Text);
            getMessage(message);
            message_box.Text = message.ToString();
        }

        private void AddPerson_Click(object sender, RoutedEventArgs e)
        {
            StringBuilder message = new StringBuilder(10 * 1024);
            personManger(0, value_person_box.Text, value_group_box.Text, value_faceId_box.Text);
            getMessage(message);
            message_box.Text = message.ToString();
        }

        private void DeletePerson_Click(object sender, RoutedEventArgs e)
        {
            StringBuilder message = new StringBuilder(10 * 1024);
            personManger(1, value_person_box.Text, value_group_box.Text, value_faceId_box.Text);

            getMessage(message);
            message_box.Text = message.ToString();
        }

        private void DetectFace_Click(object sender, RoutedEventArgs e)
        {
            StringBuilder message = new StringBuilder(10 * 1024);
            StringBuilder result = new StringBuilder(10 * 1024);
            detectManger(url_box.Text, result);
            getMessage(message);
            message_box.Text = message.ToString();
            Reslut.Text = result.ToString();

        }

        private void RecoFace_Click(object sender, RoutedEventArgs e)
        {
            StringBuilder result = new StringBuilder(10 * 1024);
            StringBuilder message = new StringBuilder(10 * 1024);
            recManger(0, url_box.Text, value_group_box.Text, result);
            getMessage(message);
            message_box.Text = message.ToString();
            Reslut.Text = result.ToString();

        }

        private void Train_Click(object sender, RoutedEventArgs e)
        {
            StringBuilder message = new StringBuilder(10 * 1024);
            trainManger(4, value_person_box.Text);
            getMessage(message);
            message_box.Text = message.ToString();
        }

        private void Train_group_Click(object sender, RoutedEventArgs e)
        {
            StringBuilder message = new StringBuilder(10 * 1024); 
            trainManger(5, value_group_box.Text);
            getMessage(message);
            message_box.Text = message.ToString();
        }

        private void AddFace_Click(object sender, RoutedEventArgs e)
        {
            StringBuilder message = new StringBuilder(10 * 1024);
            personManger(2, value_person_box.Text, value_group_box.Text, value_faceId_box.Text);

            getMessage(message);
            message_box.Text = message.ToString();
        }

        private void RemoveFace_Click(object sender, RoutedEventArgs e)
        {
            StringBuilder message = new StringBuilder(10 * 1024);
            personManger(3, value_person_box.Text, value_group_box.Text, value_faceId_box.Text);

            getMessage(message);
            message_box.Text = message.ToString();
        }
    }
}
