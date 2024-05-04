using Microsoft.AspNetCore.Mvc;

namespace WhiteLagoon.Web.Controllers
{
    public class VillaController : Controller
    {
        public IActionResult Index()
        {
            return View();
        }
    }
}
