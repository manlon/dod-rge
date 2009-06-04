using System.Runtime.InteropServices;

namespace DmdlExporterXML
{
    [Guid("885DD576-4317-41f6-8517-64AE3A3B460C")]
    [ComVisible(true)]
    /*
     *  IControl interface, it implemented in the C++ dll. 
     */
    public interface IIOControl
    {
    //    Dir2XmlData.ICast GetCast(Config cfg);
     //   Dir2XmlData.IMovie GetMovie(Config cfg);
      //  Dir2XmlData.IDefaultConfig GetDefaultConfig();
    }

    /*
     *  Control class, only save a interface pointer of the IControl.
     */
    public class IOControl
    {
        private static IIOControl inst = null;

        /// <summary>
        /// Get and set the interface pointer variable of the IControl.
        /// </summary>
        public static IIOControl Instance
        {
            get { return inst; }
            set { inst = value; }
        }
    }
}