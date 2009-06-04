using System;
using System.Runtime.InteropServices;
using System.Windows.Forms;

namespace DmdlExporterEntry
{
    [Guid("8B1E9531-98EF-4c86-83D7-9F2B3BDAE30E")]
    [ComVisible(true)]

    /*
     *  IEntry interface, this interface only provide one method 'start'.
     */
    public interface IEntry
    {
        //void start(Dir2XmlData.IControl rControl, string classname);
        void start(DmdlExporterXML.IIOControl rControl);
    }

    /*
     *  Entry class, it implemented the IEntry interface.
     */
    public class Entry : IEntry
    {
        /// <summary>
        /// Implements the only interface methods 'start', it is called in the C++ code.
        /// </summary>
        /// <param name="rControl">A control interface pointer be passed in.</param>
        //public void start(Dir2XmlData.IControl rControl, string classname)
        public void start(DmdlExporterXML.IIOControl rControl)
        {
            // save the interface pointer
            DmdlExporterXML.IOControl.Instance = rControl;

            DmdlExporterUI.MainDialog dlg = new DmdlExporterUI.MainDialog();

            dlg.ShowDialog();
            // start ui dialog
           // Dir2XmlUI.DirectorToXMLDialog dlg = new Dir2XmlUI.DirectorToXMLDialog(classname);
        }
    }
}
