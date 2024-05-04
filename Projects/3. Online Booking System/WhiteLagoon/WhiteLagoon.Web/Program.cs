using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.Configuration.AzureAppConfiguration;
using WhiteLagoon.Infrastructure.Data;

var builder = WebApplication.CreateBuilder(args);

// Retrieve the Azure App Configuration Store Connection String
string azureAppConfigurationConnectionString = builder.Configuration.GetConnectionString("AppConfig");

// Add Azure App Configuration Store
builder.Configuration.AddAzureAppConfiguration(options =>
{
    options.Connect(azureAppConfigurationConnectionString)
        .Select(KeyFilter.Any, "WhiteLagoon");
}
);

// Bind Configuration "WhiteLagoon:ConnectionStrings" to the ConnectionStrings class

// Add services to the container.
builder.Services.AddControllersWithViews();
builder.Services.AddDbContext<ApplicationDbContext>(options =>
{
    options.UseSqlServer(builder.Configuration.GetConnectionString("DefaultConnection"));
});


var app = builder.Build();

// Configure the HTTP request pipeline.
if (!app.Environment.IsDevelopment())
{
    app.UseExceptionHandler("/Home/Error");
    // The default HSTS value is 30 days. You may want to change this for production scenarios, see https://aka.ms/aspnetcore-hsts.
    app.UseHsts();
}

app.UseHttpsRedirection();
app.UseStaticFiles();

app.UseRouting();

app.UseAuthorization();

app.MapControllerRoute(
    name: "default",
    pattern: "{controller=Home}/{action=Index}/{id?}");

app.Run();
