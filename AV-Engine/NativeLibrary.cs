using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using XBlueprintBlue;

namespace AVXFramework
{
    internal class NativeLibrary
    {
        [DllImport("nativelib.dll")]
        private static extern UInt64 create_statement(byte[] buffer);

        [DllImport("nativelib.dll")]
        private static extern IntPtr exec_statement(UInt64 address);

        [DllImport("nativelib.dll")]
        private static extern Int32 free_statement(UInt64 address);
    }
}
